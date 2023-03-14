/**
 * @file int.c
 * @author 王彬浩 (SPGGOGOGO@outlook.com)
 * @brief kernel层，中断相关函数
 * @version 1.0
 * @date 2022-07-24
 * @copyright Copyright (c) 2022
 * @revisionHistory 
 *  <table> 
 *   <tr><th> 版本 <th>作者 <th>日期 <th>修改内容 
 *   <tr><td> 0.1 <td>jivin <td>2010-03-08 <td>Created 
 *   <tr><td> 1.0 <td>王彬浩 <td> 2022-07-24 <td>Standardized 
 *  </table>
 */
#include "type.h"
#include "hal.h"
#include "lsched.h"
#include "int.h"
#include "plic.h"

/**
 * @brief 中断初始化函数
 * 
 */
void acoral_intr_sys_init()
{
	acoral_u32 i;

	/*关中断*/
	acoral_intr_disable();

	/*中断嵌套标志初始化*/
	HAL_INTR_NESTING_INIT();

	/*中断底层初始化函数*/
	plic_init();
}
