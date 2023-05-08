/**
 * @file sem.h
 * @author 王彬浩 (SPGGOGOGO@outlook.com)
 * @brief kernel层，信号量相关头文件
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


#ifndef _ACORAL_SEM_H
#define _ACORAL_SEM_H

#include "event.h"

enum acoralSemRetValEnum{
    SEM_SUCCED,
    SEM_THREAD_SUSPEND,
    SEM_ERR_NULL,
    SEM_ERR_RES_NUM,
    SEM_ERR_TYPE,
    SEM_ERR_TASK_EXIST,
    SEM_ERR_INTR,
    SEM_ERR_UNDEF,
    SEM_ERR_TIMEOUT
};

enum acoralSemResAvailabiltyEnum{
    SEM_RES_AVAI,
    SEM_RES_NOAVAI
};

unsigned int   *acoral_sem_init(acoral_evt_t*,unsigned int);
acoral_evt_t *acoral_sem_create(unsigned int);
unsigned int   acoral_sem_del(acoral_evt_t *, unsigned int);
unsigned int   acoral_sem_pend(acoral_evt_t*, unsigned int);
unsigned int   acoral_sem_post(acoral_evt_t*);
int    acoral_sem_getnum(acoral_evt_t*);
#endif
