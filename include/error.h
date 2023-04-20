/**
 * @file error.h
 * @author 王彬浩 (SPGGOGOGO@outlook.com)
 * @brief kernel层，aCoral错误号定义
 * @version 1.0
 * @date 2023-04-19
 * @copyright Copyright (c) 2023
 * @revisionHistory 
 *  <table> 
 *   <tr><th> 版本 <th>作者 <th>日期 <th>修改内容 
 *   <tr><td> 0.1 <td>jivin <td>2010-03-08 <td>Created 
 *   <tr><td> 1.0 <td>王彬浩 <td> 2022-07-08 <td>Standardized 
 *   <tr><td> 1.1 <td>王彬浩 <td> 2023-04-19 <td>use enum
 *  </table>
 */
#ifndef ACORAL_ERR_H
#define ACORAL_ERR_H

enum acoralThreadError{
    ACORAL_ERR_THREAD,
    ACORAL_ERR_THREAD_DELAY,
    ACORAL_ERR_THREAD_NO_STACK  ///<线程栈指针为空
};


enum acoralMessgaeError{
    MST_ERR_NULL,
    MST_ERR_INTR,
    MST_ERR_TIMEOUT,
    MST_ERR_UNDEF,
    MSG_ERR_COUNT,
    MSGCTR_SUCCED,
    MSG_ERR_NULL
};

#endif
