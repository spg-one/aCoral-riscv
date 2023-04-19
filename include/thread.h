/**
 * @file thread.h
 * @author 王彬浩 (SPGGOGOGO@outlook.com)
 * @brief kernel层，线程优先级、控制块定义，线程管理函数声明
 * @version 1.1
 * @date 2023-04-19
 * @copyright Copyright (c) 2022
 * @revisionHistory 
 *  <table> 
 *   <tr><th> 版本 <th>作者 <th>日期 <th>修改内容 
 *   <tr><td> 0.1 <td>pegasus <td>2010-07-19 <td>增加timeout链表，用来处理超时，挂g_timeout_queue
 *   <tr><td> 1.0 <td>王彬浩 <td> 2022-06-24 <td>Standardized 
 * 	 <tr><td> 1.0 <td>王彬浩 <td> 2023-04-19 <td>use enum 
 *  </table>
 */

#ifndef ACORAL_THREAD_H
#define ACORAL_THREAD_H
#include <autocfg.h>
#include "type.h"
#include "list.h"
#include "mem.h"
#include "queue.h"
#include "event.h"

///41。总共有40个线程，就有0~40共41个优先级
#define ACORAL_MAX_PRIO_NUM ((CFG_MAX_THREAD + 1) & 0xff)
///aCoral最低优先级40
#define ACORAL_MINI_PRIO CFG_MAX_THREAD

enum acoralPrioEnum{
	ACORAL_INIT_PRIO,	//init线程独有的0优先级
	ACORAL_MAX_PRIO,	//aCoral系统中允许的最高优先级
	ACORAL_HARD_RT_PRIO_MAX,	//硬实时任务最高优先级
	ACORAL_HARD_RT_PRIO_MIN = ACORAL_HARD_RT_PRIO_MAX+CFG_HARD_RT_PRIO_NUM,	//硬实时任务最低优先级
	ACORAL_NONHARD_RT_PRIO_MAX,	//非硬实时任务最高优先级

	ACORAL_DAEMON_PRIO = ACORAL_MINI_PRIO-2,	//daemon回收线程专用优先级
	ACORAL_NONHARD_RT_PRIO_MIN,	//非硬实时任务最低优先级
	ACORAL_IDLE_PRIO	//idle线程专用优先级，也是系统最低优先级
};

enum acoralPrioTypeEnum{
	ACORAL_NONHARD_PRIO,	//非硬实时任务的优先级，会将tcb中的prio加上ACORAL_NONHARD_RT_PRIO_MAX
	ACORAL_HARD_PRIO	//硬实时任务优先级，会将tcb中的prio加上ACORAL_HARD_RT_PRIO_MAX
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
	acoral_u8 state;
	acoral_u8 prio;
	acoral_u8 policy;
	acoral_list_t ready;
	acoral_list_t timeout;
	acoral_list_t waiting;
	acoral_list_t global_list;
	acoral_evt_t* evt;
	acoral_u32 *stack;
	acoral_u32 *stack_buttom;
	acoral_u32 stack_size;
	acoral_32 delay;
	acoral_char *name;
	acoral_id console_id; ///<deprecated
	void*	private_data;
	void*	data;
}acoral_thread_t;

acoral_id create_thread_ext(void (*route)(void *args),acoral_u32 stack_size,void *args,acoral_char *name,void *stack,acoral_u32 sched_policy,void *data);
#define acoral_create_thread(route,stack_size,args,name,stack,policy,policy_data) create_thread_ext(route,stack_size,args,name,stack,policy,policy_data);
void acoral_release_thread(acoral_res_t *thread);
void acoral_suspend_self(void);
void acoral_suspend_thread_by_id(acoral_u32 thread_id);
void acoral_suspend_thread(acoral_thread_t *thread);
void acoral_resume_thread_by_id(acoral_u32 thread_id);
void acoral_resume_thread(acoral_thread_t *thread);
acoral_err acoral_wait_thread(acoral_thread_t *thread);
void acoral_delay_self(acoral_u32 ticks);
void acoral_kill_thread(acoral_thread_t *thread);
void acoral_kill_thread_by_id(acoral_id id);
void acoral_thread_exit(void);
void acoral_wake_waiting(acoral_thread_t *thread);
acoral_err acoral_thread_init(acoral_thread_t *thread,void (*route)(void *args),void (*exit)(void),void *args);
acoral_thread_t *acoral_alloc_thread(void);
void acoral_thread_pool_init(void);
void acoral_waitqueue_del(acoral_thread_t *thread);
void acoral_thread_sys_init(void);
void acoral_unrdy_thread(acoral_thread_t *thread);
void acoral_rdy_thread(acoral_thread_t *thread);
void acoral_thread_move2_tail_by_id(acoral_id thread_id);
void acoral_thread_move2_tail(acoral_thread_t *thread);
extern acoral_queue_t acoral_threads_queue;
void acoral_thread_change_prio(acoral_thread_t* thread, acoral_u32 prio);
void acoral_change_prio_self(acoral_u32 prio);
#endif

