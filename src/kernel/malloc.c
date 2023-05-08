/**
 * @file malloc.c
 * @author 王彬浩 (SPGGOGOGO@outlook.com)
 * @brief kernel层，内存malloc
 * @version 1.0
 * @date 2023-04-21
 * @copyright Copyright (c) 2023
 * @revisionHistory
 *  <table>
 *   <tr><th> 版本 <th>作者 <th>日期 <th>修改内容
 *   <tr><td> 0.1 <td>jivin <td>2010-03-08 <td>Created
 *   <tr><td> 1.0 <td>王彬浩 <td> 2023-04-21 <td>Standardized
 *  </table>
 */

#include "mutex.h"
#include "mem.h"
#include "thread.h"
#include <stdio.h>

struct mem2_ctrl_t
{
	acoral_evt_t mutex;
	char *top_p;
	char *down_p;
	unsigned int *freep_p;
	unsigned char mem_state;
} mem_ctrl;

static void *r_malloc(int size)
{
	unsigned int *tp;
	char *ctp;
	unsigned int b_size;
	size = size + 4;
	while (acoral_mutex_pend(&mem_ctrl.mutex, 0) != MUTEX_SUCCED)
		acoral_suspend_self();

	tp = mem_ctrl.freep_p;
	ctp = (char *)tp;
	while (ctp < mem_ctrl.top_p)
	{
		b_size = BLOCK_SIZE(*tp);
		if (b_size == 0)
		{
			printf("Err address is 0x%x,size should not be 0", (unsigned int)tp);
			acoral_mutex_post(&mem_ctrl.mutex);
			return NULL;
		}
		if (BLOCK_USED(*tp) || b_size < size)
		{
			ctp = ctp + b_size;
			tp = (unsigned int *)ctp;
		}
		else
		{
			BLOCK_SET_USED(tp, size);
			ctp = ctp + size;
			tp = (unsigned int *)ctp;
			if (b_size - size > 0)
				BLOCK_SET_FREE(tp, b_size - size);
			mem_ctrl.freep_p = tp;

			acoral_mutex_post(&mem_ctrl.mutex);
			return (void *)(ctp - size + 4);
		}
	}
	ctp = mem_ctrl.down_p;
	tp = (unsigned int *)ctp;
	while (tp < mem_ctrl.freep_p)
	{
		b_size = BLOCK_SIZE(*tp);
		if (b_size == 0)
		{
			printf("Err address is 0x%x,size should not be 0", (unsigned int)tp);
			acoral_mutex_post(&mem_ctrl.mutex);
			return NULL;
		}
		if (BLOCK_USED(*tp) || b_size < size)
		{
			ctp = ctp + b_size;
			tp = (unsigned int *)ctp;
		}
		else
		{
			BLOCK_SET_USED(tp, size);
			ctp = ctp + size;
			tp = (unsigned int *)ctp;
			if (b_size - size > 0)
				BLOCK_SET_FREE(tp, b_size - size);
			mem_ctrl.freep_p = tp;

			acoral_mutex_post(&mem_ctrl.mutex);
			return (void *)(ctp - size + 4);
		}
	}
	acoral_mutex_post(&mem_ctrl.mutex);
	return NULL;
}

void *v_malloc(int size)
{
	if (mem_ctrl.mem_state == 0)
		return NULL;
	size = (size + 3) & ~3;
	return r_malloc(size);
}

void v_free(void *p)
{
	unsigned int *tp, *prev_tp;
	char *ctp;
	unsigned int b_size, size = 0;
	if (mem_ctrl.mem_state == 0)
		return;
	p = (char *)p - 4;
	tp = (unsigned int *)p;
	while (acoral_mutex_pend(&mem_ctrl.mutex, 0) != 0) // 周期性任务
		acoral_suspend_self();
	if (p == NULL || (char *)p < mem_ctrl.down_p || (char *)p >= mem_ctrl.top_p || !BLOCK_CHECK(*tp))
	{
		printf("Invalide Free address:0x%x\n", (unsigned int)tp);
		return;
	}
	if (BLOCK_FREE(*tp))
	{
		printf("Address:0x%x have been freed\n", (unsigned int)tp);
		return;
	}
	prev_tp = tp;
	ctp = (char *)tp;
	b_size = BLOCK_SIZE(*tp);

	ctp = ctp + b_size;
	tp = (unsigned int *)ctp;
	if (BLOCK_FREE(*tp))
	{
		size = BLOCK_SIZE(*tp);
		if (size == 0)
		{
			printf("Err address is 0x%x,size should not be 0", (unsigned int)tp);
			acoral_mutex_post(&mem_ctrl.mutex);
			return;
		}
		b_size += size;
		BLOCK_CLEAR(tp);
	}
	BLOCK_SET_FREE(prev_tp, b_size);
	mem_ctrl.freep_p = prev_tp;
	if (p == mem_ctrl.down_p)
	{

		acoral_mutex_post(&mem_ctrl.mutex);
		return;
	}
	ctp = mem_ctrl.down_p;
	tp = (unsigned int *)ctp;
	while (ctp < (char *)p)
	{
		size = BLOCK_SIZE(*tp);
		if (size == 0)
		{
			printf("err address is 0x%x,size should not be 0", (unsigned int)tp);
			acoral_mutex_post(&mem_ctrl.mutex);
			return;
		}
		ctp = ctp + size;
		prev_tp = tp;
		tp = (unsigned int *)ctp;
	}
	if (BLOCK_FREE(*prev_tp))
	{
		tp = (unsigned int *)p;
		BLOCK_CLEAR(tp);
		BLOCK_SET_FREE(prev_tp, b_size + size);
		mem_ctrl.freep_p = prev_tp;
	}

	acoral_mutex_post(&mem_ctrl.mutex);
}

void v_mem_init()
{
	unsigned int size;
	size = acoral_malloc_size(CFG_MEM2_SIZE);
	mem_ctrl.down_p = (char *)acoral_malloc(size);
	if (mem_ctrl.down_p == NULL)
	{
		mem_ctrl.mem_state = 0;
		return;
	}
	else
	{
		mem_ctrl.mem_state = 1;
	}
	acoral_mutex_init(&mem_ctrl.mutex, 0);
	mem_ctrl.top_p = mem_ctrl.down_p + size;
	mem_ctrl.freep_p = (unsigned int *)mem_ctrl.down_p;
	BLOCK_SET_FREE(mem_ctrl.freep_p, size);
}

void v_mem_scan(void)
{
	char *ctp;
	unsigned int *tp;
	unsigned int size;
	if (mem_ctrl.mem_state == 0)
	{
		printf("Mem Init Err ,so no mem space to malloc\r\n");
		return;
	}
	ctp = mem_ctrl.down_p;
	do
	{
		tp = (unsigned int *)ctp;
		size = BLOCK_SIZE(*tp);
		if (size == 0)
		{
			printf("Err address is 0x%x,size should not be 0\r\n", (unsigned int)tp);
			break;
		}
		if (BLOCK_USED(*tp))
		{
			printf("The address is 0x%x,the block is used and it's size is %d\r\n", (unsigned int)tp, size);
		}
		else
		{

			printf("The address is 0x%x,the block is unused and it's size is %d\r\n", (unsigned int)tp, size);
		}
		ctp = ctp + size;
	} while (ctp < mem_ctrl.top_p);
}
