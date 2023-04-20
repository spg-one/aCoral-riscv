
#include "hal.h"
#include "queue.h"
#include "thread.h"
#include "policy.h"
#include "int.h"
#include <stdio.h>
#include "comm_thrd.h"
#include "period_thrd.h"

acoral_queue_t policy_list;

acoral_sched_policy_t *acoral_get_policy_ctrl(unsigned char type){
	acoral_list_t   *tmp,*head;
	acoral_sched_policy_t  *policy_ctrl;
	head=&policy_list.head;
	tmp=head;
	for(tmp=head->next;tmp!=head;tmp=tmp->next){
		policy_ctrl=list_entry(tmp,acoral_sched_policy_t,list);
		if(policy_ctrl->type==type)
			return policy_ctrl;
	}
	return NULL;
}

int acoral_policy_thread_init(unsigned int policy,acoral_thread_t *thread,void (*route)(void *args),void *args,void *data){
	acoral_sched_policy_t   *policy_ctrl;
	policy_ctrl=acoral_get_policy_ctrl(policy);	
	if(policy_ctrl==NULL||policy_ctrl->policy_thread_init==NULL){
		acoral_enter_critical();
		acoral_release_res((acoral_res_t *)thread);
		acoral_exit_critical();
		printf("No thread policy support:%d\n",thread->policy);
		return -1;
	}
	return policy_ctrl->policy_thread_init(thread,route,args,data);
}

void acoral_register_sched_policy(acoral_sched_policy_t *policy){
	acoral_list_add2_tail(&policy->list,&policy_list.head);
}

void acoral_policy_delay_deal(){
	acoral_list_t   *tmp,*head;
	acoral_sched_policy_t  *policy_ctrl;
	head=&policy_list.head;
	tmp=head;
	for(tmp=head->next;tmp!=head;tmp=tmp->next){
		policy_ctrl=list_entry(tmp,acoral_sched_policy_t,list);
		if(policy_ctrl->delay_deal!=NULL)
			policy_ctrl->delay_deal();
	}
}

void acoral_policy_thread_release(acoral_thread_t *thread){
	acoral_sched_policy_t   *policy_ctrl;
	policy_ctrl=acoral_get_policy_ctrl(thread->policy);
	if(policy_ctrl->policy_thread_release!=NULL)
		policy_ctrl->policy_thread_release(thread);
}


void acoral_sched_policy_init(){
	acoral_init_list(&policy_list.head);
	comm_policy_init();

#ifdef CFG_THRD_PERIOD
	period_policy_init();
#endif
}


