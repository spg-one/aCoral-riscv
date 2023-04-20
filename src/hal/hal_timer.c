/**
 * @file hal_timer.c
 * @author 王彬浩 (SPGGOGOGO@outlook.com)
 * @brief hal层，定时器硬件初始化代码
 * @version 1.0
 * @date 2022-07-17
 * @copyright Copyright (c) 2023
 * @revisionHistory 
 *  <table> 
 *   <tr><th> 版本 <th>作者 <th>日期 <th>修改内容 
 *   <tr><td> 0.1 <td>jivin <td>2010-03-08 <td>Created 
 *   <tr><td> 1.0 <td>王彬浩 <td> 2022-07-17 <td>Standardized 
 *  </table>
 */

#include "core.h"
#include "hal_timer.h"
#include "clint.h"

/**
 * @brief 初始化定时器0，用于时钟tick
 * 
 */
void hal_ticks_init(){
  	clint_timer_init();
}
