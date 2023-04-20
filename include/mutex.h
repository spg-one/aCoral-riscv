/**
 * @file mutex.h
 * @author 王彬浩 (SPGGOGOGO@outlook.com)
 * @brief kernel层，互斥量头文件
 * @version 1.1
 * @date 2023-04-20
 * @copyright Copyright (c) 2023
 * @revisionHistory
 *  <table>
 *   <tr><th> 版本 <th>作者 <th>日期 <th>修改内容
 *   <tr><td> 0.1 <td>jivin <td>2010-03-08 <td>Created
 *   <tr><td> 1.0 <td>王彬浩 <td> 2022-07-28 <td>Standardized
 *   <tr><td> 1.1 <td>王彬浩 <td> 2023-04-20 <td>optimized 
 *  </table>
 */

#ifndef _ACORAL_MUTEX_H
#define _ACORAL_MUTEX_H
#include "type.h"
#include "event.h"

#define MUTEX_AVAI 0x00FF

#define MUTEX_L_MASK 0x00FF
#define MUTEX_U_MASK 0xFF00
#define MUTEX_CEILING_MASK 0xFF0000

enum acoralMutexRetVal{
    MUTEX_SUCCED,
    MUTEX_THREAD_SUSPEND,
    MUTEX_ERR_NULL,
    MUTEX_ERR_TYPE,
    MUTEX_ERR_TASK_EXIST,
    MUTEX_ERR_INTR,
    MUTEX_ERR_UNDEF,
    MUTEX_ERR_TIMEOUT,
    MUTEX_ERR_RDY
};

acoral_u32 acoral_mutex_init(acoral_evt_t *, acoral_u8);
acoral_evt_t *acoral_mutex_create(acoral_u8, acoral_u32 *);
acoral_u32 acoral_mutex_del(acoral_evt_t *, acoral_u32);
acoral_u32 acoral_mutex_pend(acoral_evt_t *, acoral_u32);
acoral_u32 acoral_mutex_post(acoral_evt_t *);
acoral_u32 acoral_mutex_trypend(acoral_evt_t *);

#endif
