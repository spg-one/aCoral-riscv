/**
 * @file thread.h
 * @author 王彬浩 (SPGGOGOGO@outlook.com)
 * @brief kernel层，线程优先级、控制块定义，线程管理函数声明
 * @version 1.1
 * @date 2023-04-19
 * @copyright Copyright (c) 2023
 * @revisionHistory 
 *  <table> 
 *   <tr><th> 版本 <th>作者 <th>日期 <th>修改内容 
 *   <tr><td> 0.1 <td>pegasus <td>2010-07-19 <td>增加timeout链表，用来处理超时，挂g_timeout_queue
 *   <tr><td> 1.0 <td>王彬浩 <td> 2022-06-24 <td>Standardized 
 * 	 <tr><td> 1.1 <td>王彬浩 <td> 2023-04-19 <td>use enum 
 *  </table>
 */

#ifndef ACORAL_THREAD_H
#define ACORAL_THREAD_H
#include "autocfg.h"
#include "list.h"
#include "mem.h"
#include "event.h"

#define ACORAL_MAX_PRIO_NUM ((CFG_MAX_THREAD + 1) & 0xff) ///<41。总共有40个线程，就有0~40共41个优先级
#define ACORAL_MINI_PRIO CFG_MAX_THREAD ///<aCoral最低优先级40

enum acoralPrioEnum{
	ACORAL_INIT_PRIO,	///<init线程独有的0优先级
	ACORAL_MAX_PRIO,	///<aCoral系统中允许的最高优先级
	ACORAL_HARD_RT_PRIO_MAX,	///<硬实时任务最高优先级
	ACORAL_HARD_RT_PRIO_MIN = ACORAL_HARD_RT_PRIO_MAX+CFG_HARD_RT_PRIO_NUM,	///<硬实时任务最低优先级
	ACORAL_NONHARD_RT_PRIO_MAX,	///<非硬实时任务最高优先级

	ACORAL_DAEMON_PRIO = ACORAL_MINI_PRIO-2,	///<daemon回收线程专用优先级
	ACORAL_NONHARD_RT_PRIO_MIN,	///<非硬实时任务最低优先级
	ACORAL_IDLE_PRIO	///<idle线程专用优先级，也是系统最低优先级ACORAL_MINI_PRIO
};

enum acoralPrioTypeEnum{
	ACORAL_NONHARD_PRIO,	///<非硬实时任务的优先级，会将tcb中的prio加上ACORAL_NONHARD_RT_PRIO_MAX
	ACORAL_HARD_PRIO	///<硬实时任务优先级，会将tcb中的prio加上ACORAL_HARD_RT_PRIO_MAX
};

enum acoralThreadState{
	ACORAL_THREAD_STATE_READY = 1,
	ACORAL_THREAD_STATE_SUSPEND = 1<<1,
	ACORAL_THREAD_STATE_RUNNING = 1<<2,
	ACORAL_THREAD_STATE_EXIT = 1<<3,
	ACORAL_THREAD_STATE_RELEASE = 1<<4,
	ACORAL_THREAD_STATE_DELAY = 1<<5,
	ACORAL_THREAD_STATE_MOVE = 1<<6
};

/**
 * 
 *  @struct acoral_thread_t
 *  @brief 线程控制块TCB
 * 
 * 
 */
typedef struct{
  	acoral_res_t res;	///<资源id，线程创建后作为线程id
	unsigned char state;
	unsigned char prio;
	unsigned char policy;
	acoral_list_t ready;	///<用于挂载到全局就绪队列
	acoral_list_t timeout;
	acoral_list_t waiting;
	acoral_list_t global_list;
	acoral_evt_t* evt;
	unsigned int *stack;
	unsigned int *stack_buttom;
	unsigned int stack_size;
	int delay;
	char *name;
	int console_id; ///<deprecated
	void*	private_data;
	void*	data;
}acoral_thread_t;

/**
 * @brief 创建一个线程
 * 
 * @param route 线程函数
 * @param stack_size 线程栈大小
 * @param args 线程函数参数
 * @param name 线程名字
 * @param stack 线程栈指针
 * @param sched_policy 线程调度策略
 * @param data 线程策略数据
 * @return int 返回线程id
 */
int acoral_create_thread(void (*route)(void *args),unsigned int stack_size,void *args,char *name,void *stack,unsigned int sched_policy,void *data);
void acoral_release_thread(acoral_res_t *thread);
void acoral_suspend_self(void);
void acoral_suspend_thread_by_id(unsigned int thread_id);
void acoral_suspend_thread(acoral_thread_t *thread);
void acoral_resume_thread_by_id(unsigned int thread_id);
void acoral_resume_thread(acoral_thread_t *thread);
unsigned int acoral_wait_thread(acoral_thread_t *thread);
void acoral_delay_self(unsigned int ticks);
void acoral_kill_thread(acoral_thread_t *thread);
void acoral_kill_thread_by_id(int id);
void acoral_thread_exit(void);
void acoral_wake_waiting(acoral_thread_t *thread);
unsigned int acoral_thread_init(acoral_thread_t *thread,void (*route)(void *args),void (*exit)(void),void *args);
acoral_thread_t *acoral_alloc_thread(void);
void acoral_thread_pool_init(void);
void acoral_waitqueue_del(acoral_thread_t *thread);
void acoral_thread_sys_init(void);
void acoral_unrdy_thread(acoral_thread_t *thread);
void acoral_rdy_thread(acoral_thread_t *thread);
void acoral_thread_move2_tail_by_id(int thread_id);
void acoral_thread_move2_tail(acoral_thread_t *thread);
extern acoral_list_t acoral_threads_queue;
void acoral_thread_change_prio(acoral_thread_t* thread, unsigned int prio);
void acoral_change_prio_self(unsigned int prio);
#endif

