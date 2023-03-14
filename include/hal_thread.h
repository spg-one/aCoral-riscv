/**
 * @file hal_thread.h
 * @author 王彬浩 (SPGGOGOGO@outlook.com)
 * @brief hal层，线程相关头文件
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

#ifndef HAL_THREAD_H
#define HAL_THREAD_H

/**
 * @brief aCoral线程上下文context在硬件层面的描述
 */
typedef struct {
  	acoral_u64 ra; ///<程序状态寄存器
	acoral_u64 sp; ///<通用寄存器
	acoral_u64 s0; ///<通用寄存器
	acoral_u64 s1; ///<通用寄存器
	acoral_u64 a0; ///<通用寄存器
	acoral_u64 a1; ///<通用寄存器
	acoral_u64 a2; ///<通用寄存器
	acoral_u64 a3; ///<通用寄存器
	acoral_u64 a4; ///<通用寄存器
	acoral_u64 a5; ///<通用寄存器
	acoral_u64 a6; ///<通用寄存器
	acoral_u64 a7; ///<通用寄存器
	acoral_u64 s2; ///<通用寄存器
	acoral_u64 s3; ///<通用寄存器
	acoral_u64 s4; ///<通用寄存器
	acoral_u64 s5; ///<通用寄存器
	acoral_u64 s6; ///<通用寄存器
	acoral_u64 s7; ///<通用寄存器
	acoral_u64 s8; ///<通用寄存器
	acoral_u64 s9; ///<通用寄存器
	acoral_u64 s10; ///<通用寄存器
	acoral_u64 s11; ///<通用寄存器
}hal_ctx_t;

void HAL_SWITCH_TO(acoral_u32** next);
void HAL_CONTEXT_SWITCH(acoral_u32 **prev , acoral_u32 **next);
void HAL_INTR_SWITCH_TO(acoral_u32 **next);
void HAL_INTR_CTX_SWITCH(acoral_u32 **prev , acoral_u32 **next);
void hal_stack_init(acoral_u32 **stk,void (*route)(void),void (*exit)(void),void *args);

//线程相关的硬件抽象接口 //TODO 全大写为了和汇编接口统一
#define HAL_STACK_INIT(stack,route,exit,args) hal_stack_init(stack,route,exit,args)

#endif