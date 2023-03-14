/**
 * @file hal_int.h
 * @author 王彬浩 (SPGGOGOGO@outlook.com)
 * @brief hal层，中断相关头文件
 * @version 1.0
 * @date 2022-07-17
 * @copyright Copyright (c) 2022
 * @revisionHistory 
 *  <table> 
 *   <tr><th> 版本 <th>作者 <th>日期 <th>修改内容 
 *   <tr><td> 0.1 <td>jivin <td>2010-03-08 <td>Created 
 *   <tr><td> 1.0 <td>王彬浩 <td> 2022-07-17 <td>Standardized 
 *  </table>
 */
#ifndef HAL_INT_H
#define HAL_INT_H

#include "type.h"

#define HAL_INTR_ENABLE()                  __asm volatile  ( "csrc mstatus,8" )
#define HAL_INTR_DISABLE()                 __asm volatile  ( "csrs mstatus,8" )

void hal_intr_unmask(acoral_vector vector);
void hal_intr_mask(acoral_vector vector);
void hal_intr_ack(acoral_u32 vector);
void hal_intr_init(void);
void hal_intr_nesting_init_comm();
acoral_u32 hal_get_intr_nesting_comm();
void hal_intr_nesting_dec_comm();
void hal_intr_nesting_inc_comm();
void hal_sched_bridge_comm();
void hal_intr_exit_bridge_comm();

/****************************                                                                                                                 
* the comm interrupt interface of hal     
*  hal层中断部分通用接口
*****************************/

#define HAL_INTR_NESTING_INIT()   hal_intr_nesting_init_comm()
#define HAL_GET_INTR_NESTING()    hal_get_intr_nesting_comm()
#define HAL_INTR_NESTING_DEC()    hal_intr_nesting_dec_comm()
#define HAL_INTR_NESTING_INC()    hal_intr_nesting_inc_comm()
#define HAL_ENTER_CRITICAL()  HAL_INTR_DISABLE()
#define HAL_EXIT_CRITICAL()  HAL_INTR_ENABLE()
#define HAL_INTR_ATTACH(vecotr,isr) //TODO 该写什么？
#define HAL_SCHED_BRIDGE() hal_sched_bridge_comm()
#define HAL_INTR_EXIT_BRIDGE() hal_intr_exit_bridge_comm()

#endif