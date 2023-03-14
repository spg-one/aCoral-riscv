/**
 * @file hal_int_c.c
 * @author 王彬浩 (SPGGOGOGO@outlook.com)
 * @brief hal层，中断二级入口、中断开关以及中断初始化c代码
 * @version 1.0
 * @date 2022-06-23
 * @copyright Copyright (c) 2022
 *
 * <table>
 * <tr><th> 版本 <th>作者 <th>日期 <th>修改内容
 * <tr><td> 0.1 <td>jivin <td>2010-3-8 <td>Created
 * <tr><td> 1.0 <td>王彬浩 <td>2022-06-23 <td>Standardized
 * </table>
 */
#include "type.h"
#include "hal_int.h"
#include "lsched.h"

///中断嵌套数
acoral_u32 intr_nesting;

/**
 * @brief 使能中断。通过向中断屏蔽（INTMSK）寄存器某位写入0来打开相应中断，对中断复用进行了合并处理
 *
 * @param vector 中断向量号（中断复用展开后）
 */
void hal_intr_unmask(acoral_vector vector)
{
	// TODO riscv-加上
}

/**
 * @brief 除能中断。通过向中断屏蔽（INTMSK）寄存器某位写入1来屏蔽相应中断，对中断复用进行了合并处理
 *
 * @param vector 中断向量号（中断复用展开后）
 */
void hal_intr_mask(acoral_vector vector)
{
	// TODO riscv-加上
}

/**
 * @brief 中断嵌套初始化
 */
void hal_intr_nesting_init_comm()
{
	intr_nesting = 0;
}

/**
 * @brief 获取系统当前中断嵌套数
 *
 * @return acoral_u32 中断嵌套数
 */
acoral_u32 hal_get_intr_nesting_comm()
{
	return intr_nesting;
}

/**
 * @brief 减少系统当前中断嵌套数
 *
 */
void hal_intr_nesting_dec_comm()
{
	if (intr_nesting > 0)
		intr_nesting--;
}

/**
 * @brief 增加系统当前中断嵌套数
 *
 */
void hal_intr_nesting_inc_comm()
{
	intr_nesting++;
}

/**
 * @brief 保证调度的原子性
 *
 */
void hal_sched_bridge_comm()
{
	HAL_ENTER_CRITICAL();
	acoral_real_sched();
	HAL_EXIT_CRITICAL();
}

/**
 * @brief 保证调度（中断引起）的原子性
 *
 */
void hal_intr_exit_bridge_comm()
{

	HAL_ENTER_CRITICAL();
	acoral_real_intr_sched();
	HAL_EXIT_CRITICAL();
}
