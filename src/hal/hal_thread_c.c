/**
 * @file hal_thread_c.c
 * @author 王彬浩 (SPGGOGOGO@outlook.com)
 * @brief hal层，线程硬件相关代码
 * @version 1.0
 * @date 2022-07-22
 * @copyright Copyright (c) 2022
 * @revisionHistory 
 *  <table> 
 *   <tr><th> 版本 <th>作者 <th>日期 <th>修改内容 
 *   <tr><td> 0.1 <td>jivin <td>2010-03-08 <td>Created 
 *   <tr><td> 1.0 <td>王彬浩 <td> 2022-07-22 <td>Standardized 
 *  </table>
 */
#include"type.h"
#include "hal_thread.h"

/**
 * @brief 线程上下文初始化，用于线程被切换到cpu上运行后，替换之前的线程的上下文
 * 
 * @param stk 栈指针
 * @param route 线程运行函数指针
 * @param exit 线程退出函数指针
 * @param args 线程运行函数参数
 */
void hal_stack_init(acoral_u32 **stk,void (*route)(),void (*exit)(),void *args){
	hal_ctx_t temp;
	hal_ctx_t *ctx=	&temp;
	ctx->ra = (acoral_u64)route;
	ctx->sp = (acoral_u64)stk;
	ctx->s0 = 0;
	ctx->s1 = 0;
	ctx->a0 = 0;
	ctx->a1 = 0;
	ctx->a2 = 0;
	ctx->a3 = 0;
	ctx->a4 = 0;
	ctx->a5 = 0;
	ctx->a6 = 0;
	ctx->a7 = 0;
	ctx->s2 = 0;
	ctx->s3 = 0;
	ctx->s4 = 0;
	ctx->s5 = 0;
	ctx->s6 = 0;
	ctx->s7 = 0;
	ctx->s8 = 0;
	ctx->s9 = 0;
	ctx->s10 = 0;
	ctx->s11 = 0;
	
    *stk=(acoral_u32 *)ctx;
}
