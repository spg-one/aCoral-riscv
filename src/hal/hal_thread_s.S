 /**
 * @file hal_thread_s.s
 * @author 王彬浩 (SPGGOGOGO@outlook.com)
 * @brief hal层，线程上下文切换操作
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


 .equ NOINT    ,	0xc0
 .equ SVCMODE  ,	0x13

.globl HAL_INTR_CTX_SWITCH
.globl HAL_CONTEXT_SWITCH
.globl HAL_INTR_SWITCH_TO
.globl HAL_SWITCH_TO

#define REGBYTES 8

HAL_SWITCH_TO:
    ld sp, 0(a0)
    ld x1, 0*REGBYTES(sp)
    ld x2, 1*REGBYTES(sp)
    ld x8, 2*REGBYTES(sp)
    ld x9, 3*REGBYTES(sp)
    ld x10, 4*REGBYTES(sp)
    ld x11, 5*REGBYTES(sp)
    ld x12, 6*REGBYTES(sp)
    ld x13, 7*REGBYTES(sp)
    ld x14, 8*REGBYTES(sp)
    ld x15, 9*REGBYTES(sp)
    ld x16, 10*REGBYTES(sp)
    ld x17, 11*REGBYTES(sp)
    ld x18, 12*REGBYTES(sp)
    ld x19, 13*REGBYTES(sp)
    ld x20, 14*REGBYTES(sp)
    ld x21, 15*REGBYTES(sp)
    ld x22, 16*REGBYTES(sp)
    ld x23, 17*REGBYTES(sp)
    ld x24, 18*REGBYTES(sp)
    ld x25, 19*REGBYTES(sp)
    ld x26, 20*REGBYTES(sp)
    ld x27, 21*REGBYTES(sp)
    addi sp, sp, 22*REGBYTES

    ret

HAL_INTR_SWITCH_TO:
    ret

HAL_INTR_CTX_SWITCH:
    ret
    

HAL_CONTEXT_SWITCH:
    addi sp, sp, -22*REGBYTES

    sd x1, 0*REGBYTES(sp)
    sd x2, 1*REGBYTES(sp)
    sd x8, 2*REGBYTES(sp)
    sd x9, 3*REGBYTES(sp)
    sd x10, 4*REGBYTES(sp)
    sd x11, 5*REGBYTES(sp)
    sd x12, 6*REGBYTES(sp)
    sd x13, 7*REGBYTES(sp)
    sd x14, 8*REGBYTES(sp)
    sd x15, 9*REGBYTES(sp)
    sd x16, 10*REGBYTES(sp)
    sd x17, 11*REGBYTES(sp)
    sd x18, 12*REGBYTES(sp)
    sd x19, 13*REGBYTES(sp)
    sd x20, 14*REGBYTES(sp)
    sd x21, 15*REGBYTES(sp)
    sd x22, 16*REGBYTES(sp)
    sd x23, 17*REGBYTES(sp)
    sd x24, 18*REGBYTES(sp)
    sd x25, 19*REGBYTES(sp)
    sd x26, 20*REGBYTES(sp)
    sd x27, 21*REGBYTES(sp)
    sd sp, 0(a0)

    ld sp, 0(a1)
    ld x1, 0*REGBYTES(sp)
    ld x2, 1*REGBYTES(sp)
    ld x8, 2*REGBYTES(sp)
    ld x9, 3*REGBYTES(sp)
    ld x10, 4*REGBYTES(sp)
    ld x11, 5*REGBYTES(sp)
    ld x12, 6*REGBYTES(sp)
    ld x13, 7*REGBYTES(sp)
    ld x14, 8*REGBYTES(sp)
    ld x15, 9*REGBYTES(sp)
    ld x16, 10*REGBYTES(sp)
    ld x17, 11*REGBYTES(sp)
    ld x18, 12*REGBYTES(sp)
    ld x19, 13*REGBYTES(sp)
    ld x20, 14*REGBYTES(sp)
    ld x21, 15*REGBYTES(sp)
    ld x22, 16*REGBYTES(sp)
    ld x23, 17*REGBYTES(sp)
    ld x24, 18*REGBYTES(sp)
    ld x25, 19*REGBYTES(sp)
    ld x26, 20*REGBYTES(sp)
    ld x27, 21*REGBYTES(sp)
    addi sp, sp, 22*REGBYTES

    ret