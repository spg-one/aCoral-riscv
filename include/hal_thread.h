/**
 * @file hal_thread.h
 * @author 王彬浩 (SPGGOGOGO@outlook.com)
 * @brief hal层，线程相关头文件
 * @version 1.1
 * @date 2023-04-120
 * @copyright Copyright (c) 2023
 * @revisionHistory 
 *  <table> 
 *   <tr><th> 版本 <th>作者 <th>日期 <th>修改内容 
 *   <tr><td> 0.1 <td>jivin <td>2010-03-08 <td>Created 
 *   <tr><td> 1.0 <td>王彬浩 <td> 2022-07-17 <td>Standardized 
 *   <tr><td> 1.1 <td>王彬浩 <td> 2023-04-20 <td>riscv
 *  </table>
 */

#ifndef HAL_THREAD_H
#define HAL_THREAD_H

/**
 * @brief aCoral线程上下文context在硬件层面的描述
 */
typedef struct {
  	acoral_u64 epc;        /* epc - epc    - program counter                     */
    acoral_u64 ra;         /* x1  - ra     - return address for jumps            */
    acoral_u64 mstatus;    /*              - machine status register             */
    acoral_u64 gp;         /* x3  - gp     - global pointer                      */
    acoral_u64 tp;         /* x4  - tp     - thread pointer                      */
    acoral_u64 t0;         /* x5  - t0     - temporary register 0                */
    acoral_u64 t1;         /* x6  - t1     - temporary register 1                */
    acoral_u64 t2;         /* x7  - t2     - temporary register 2                */
    acoral_u64 s0_fp;      /* x8  - s0/fp  - saved register 0 or frame pointer   */
    acoral_u64 s1;         /* x9  - s1     - saved register 1                    */
    acoral_u64 a0;         /* x10 - a0     - return value or function argument 0 */
    acoral_u64 a1;         /* x11 - a1     - return value or function argument 1 */
    acoral_u64 a2;         /* x12 - a2     - function argument 2                 */
    acoral_u64 a3;         /* x13 - a3     - function argument 3                 */
    acoral_u64 a4;         /* x14 - a4     - function argument 4                 */
    acoral_u64 a5;         /* x15 - a5     - function argument 5                 */
    acoral_u64 a6;         /* x16 - a6     - function argument 6                 */
    acoral_u64 a7;         /* x17 - s7     - function argument 7                 */
    acoral_u64 s2;         /* x18 - s2     - saved register 2                    */
    acoral_u64 s3;         /* x19 - s3     - saved register 3                    */
    acoral_u64 s4;         /* x20 - s4     - saved register 4                    */
    acoral_u64 s5;         /* x21 - s5     - saved register 5                    */
    acoral_u64 s6;         /* x22 - s6     - saved register 6                    */
    acoral_u64 s7;         /* x23 - s7     - saved register 7                    */
    acoral_u64 s8;         /* x24 - s8     - saved register 8                    */
    acoral_u64 s9;         /* x25 - s9     - saved register 9                    */
    acoral_u64 s10;        /* x26 - s10    - saved register 10                   */
    acoral_u64 s11;        /* x27 - s11    - saved register 11                   */
    acoral_u64 t3;         /* x28 - t3     - temporary register 3                */
    acoral_u64 t4;         /* x29 - t4     - temporary register 4                */
    acoral_u64 t5;         /* x30 - t5     - temporary register 5                */
    acoral_u64 t6;         /* x31 - t6     - temporary register 6                */
#ifdef ARCH_ACORAL_FPU
    acoral_u32 f0;      /* f0  */
    acoral_u32 f1;      /* f1  */
    acoral_u32 f2;      /* f2  */
    acoral_u32 f3;      /* f3  */
    acoral_u32 f4;      /* f4  */
    acoral_u32 f5;      /* f5  */
    acoral_u32 f6;      /* f6  */
    acoral_u32 f7;      /* f7  */
    acoral_u32 f8;      /* f8  */
    acoral_u32 f9;      /* f9  */
    acoral_u32 f10;     /* f10 */
    acoral_u32 f11;     /* f11 */
    acoral_u32 f12;     /* f12 */
    acoral_u32 f13;     /* f13 */
    acoral_u32 f14;     /* f14 */
    acoral_u32 f15;     /* f15 */
    acoral_u32 f16;     /* f16 */
    acoral_u32 f17;     /* f17 */
    acoral_u32 f18;     /* f18 */
    acoral_u32 f19;     /* f19 */
    acoral_u32 f20;     /* f20 */
    acoral_u32 f21;     /* f21 */
    acoral_u32 f22;     /* f22 */
    acoral_u32 f23;     /* f23 */
    acoral_u32 f24;     /* f24 */
    acoral_u32 f25;     /* f25 */
    acoral_u32 f26;     /* f26 */
    acoral_u32 f27;     /* f27 */
    acoral_u32 f28;     /* f28 */
    acoral_u32 f29;     /* f29 */
    acoral_u32 f30;     /* f30 */
    acoral_u32 f31;     /* f31 */
#endif
}hal_ctx_t;

void HAL_SWITCH_TO(acoral_u32** next);
void HAL_CONTEXT_SWITCH(acoral_u32 **prev , acoral_u32 **next);
void HAL_INTR_SWITCH_TO(acoral_u32 **next);
void HAL_INTR_CTX_SWITCH(acoral_u32 **prev , acoral_u32 **next);
acoral_u32* hal_stack_init(acoral_u32 *stack, void *route, void *exit, void *args);

//线程相关的硬件抽象接口 //TODO 全大写为了和汇编接口统一
#define HAL_STACK_INIT(stack,route,exit,args) hal_stack_init(stack, route,exit, args)

#endif