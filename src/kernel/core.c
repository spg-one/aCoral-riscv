/**
 * @mainpage aCoral-I源码文档
 * @section 简介
 * 珊瑚aCoral单核版本源码文档，对源码中的文件、函数、变量等进行了详细说明，适合初学者阅读，用以加深对aCoral-I的理解。\n
 * 配合《珊瑚-I 内核手册》食用更香哦。
 * @author 王彬浩 (SPGGOGOGO@outlook.com)
 * @version 1.0
 * @date 2022-06-24
 * @copyright Copyright (c) 2023
 * @revisionHistory 
 *  <table> 
 *   <tr><th> 版本 <th>作者 <th>日期 <th>修改内容 
 *   <tr><td> 0.1 <td>jivin <td>2010-03-08 <td>Created 
 *   <tr><td> 1.0 <td>王彬浩 <td> 2022-06-24 <td>Standardized 
 *  </table>
 */

/**
 * @file core.c
 * @author 王彬浩 (SPGGOGOGO@outlook.com)
 * @brief kernel层，aCoral内核初始化文件，紧接start.S
 * @version 1.0
 * @date 2022-07-04
 * @copyright Copyright (c) 2023
 * @revisionHistory 
 *  <table> 
 *   <tr><th> 版本 <th>作者 <th>日期 <th>修改内容 
 *   <tr><td> 0.1 <td>jivin <td>2010-03-08 <td>Created 
 *   <tr><td> 1.0 <td>王彬浩 <td> 2022-07-04 <td>Standardized 
 *  </table>
 */

#include "kernel.h"
#include "hal.h"
#include "lib.h"
#include <stdio.h>
acoral_queue_t acoral_res_release_queue;
volatile acoral_u32 acoral_start_sched = false;
acoral_id daemon_id, idle_id, init_id;

/**
 * @brief aCoral空闲守护线程idle函数
 *
 * @param args
 */
void idle(void *args)
{
	for(;;){}
}

/**
 * @brief aCoral资源回收线程daem函数
 *
 * @param args
 */
void daem(void *args)
{
	acoral_thread_t *thread;
	acoral_list_t *head, *tmp, *tmp1;
	head = &acoral_res_release_queue.head;
	while (1)
	{
		for (tmp = head->next; tmp != head;)
		{
			tmp1 = tmp->next;
			acoral_enter_critical();
			thread = list_entry(tmp, acoral_thread_t, waiting);
			/*如果线程资源已经不在使用，即release状态则释放*/

			acoral_list_del(tmp); /**/

			acoral_exit_critical();
			tmp = tmp1;
			if (thread->state == ACORAL_THREAD_STATE_RELEASE)
			{
				acoral_release_thread((acoral_res_t *)thread);
			}
			else
			{
				acoral_enter_critical();
				tmp1 = head->prev;
				acoral_list_add2_tail(&thread->waiting, head); /**/
				acoral_exit_critical();
			}
		}
		acoral_suspend_self();
	}
}


#define DAEM_STACK_SIZE 256

acoral_thread_t *thread;

/**
 * @brief aCoral初始化线程init函数
 *
 * @param args
 */
void init(void *args)
{
	printf("in init spg\n");
	acoral_comm_policy_data_t data;
	acoral_ticks_init();
	/*ticks中断初始化函数*/
	acoral_start_sched = true;

	/*创建后台服务进程*/
	acoral_init_list(&acoral_res_release_queue.head);
	data.prio = ACORAL_DAEMON_PRIO;
	data.prio_type = ACORAL_HARD_PRIO;
	daemon_id = acoral_create_thread(daem, DAEM_STACK_SIZE, NULL, "daemon", NULL, ACORAL_SCHED_POLICY_COMM, &data);
	thread = (acoral_thread_t *)acoral_get_res_by_id(daemon_id);
	if (daemon_id == -1)
		while (1)
			;
			/*应用级相关服务初始化,应用级不要使用延时函数，没有效果的*/
#ifdef CFG_SHELL
	acoral_shell_init();
#endif
	printf("init done\n");
}

acoral_thread_t orig_thread;

/**
 * @brief  c语言初始化入口函数
 * 
 */
void acoral_start()
{
	printf("in acoral_start\n");
	acoral_set_orig_thread(&orig_thread);
	printf("before module init\n");
	/*内核模块初始化*/
	acoral_module_init();
	printf("after module init\n");
	/*主cpu开始函数*/
	acoral_core_cpu_start();
}


/**
 * @brief CPU开始创建线程工作，创建idle线程、init线程
 * 
 */
#define IDLE_STACK_SIZE 128
void acoral_core_cpu_start()
{
	acoral_comm_policy_data_t data;
	/*创建空闲线程*/
	acoral_start_sched = false;
	data.prio = ACORAL_IDLE_PRIO;
	data.prio_type = ACORAL_HARD_PRIO;
	idle_id = acoral_create_thread(idle, IDLE_STACK_SIZE, NULL, "idle", NULL, ACORAL_SCHED_POLICY_COMM, &data);
	if (idle_id == -1)
	{
		while(1){}
	}
	/*创建初始化线程,这个调用层次比较多，需要多谢堆栈*/
	data.prio = ACORAL_INIT_PRIO;
	/*动态堆栈*/
	init_id = acoral_create_thread(init, 512, "in init", "init", NULL, ACORAL_SCHED_POLICY_COMM, &data);
	if (init_id == -1)
	{
		while (1){}
	}
		
	
	acoral_start_os();
}

/**
 * @brief aCoral最终启动
 * 
 */

void acoral_start_os()
{
	acoral_sched_init();
	acoral_select_thread();
	acoral_set_running_thread(acoral_ready_thread);//SPG空指针
	HAL_SWITCH_TO(&acoral_cur_thread->stack);
}

/**
 * @brief aCoral内核各模块初始化
 * 
 */
void acoral_module_init()
{
	/*中断系统初始化*/
	acoral_intr_sys_init();
	printf("intr_sys_init done\n");

	/*内存管理系统初始化*/
	acoral_mem_sys_init();
	printf("mem_sys_init done\n");

	/*线程管理系统初始化*/
	acoral_thread_sys_init();
	printf("thread_sys_init done\n");

	/*时钟管理系统初始化*/
	acoral_time_sys_init();
	printf("time_sys_init done\n");

	/*事件管理系统初始化*/
	acoral_evt_sys_init();
	printf("evt_sys_init done\n");
#ifdef CFG_DRIVER
	/*驱动管理系统初始化*/
	//acoral_drv_sys_init();
#endif
}
