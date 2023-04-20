/**
 * @file list.h
 * @author 王彬浩 (SPGGOGOGO@outlook.com)
 * @brief lib层
 * @version 1.0
 * @date 2023-04-19
 * @copyright Copyright (c) 2023
 * @revisionHistory 
 *  <table> 
 *   <tr><th> 版本 <th>作者 <th>日期 <th>修改内容 
 *   <tr><td> 0.1 <td>jivin <td>2010-03-08 <td>Created 
 *   <tr><td> 1.0 <td>王彬浩 <td> 2023-04-19 <td>Standardized 
 *  </table>
 */

#ifndef ACORAL_LIST_H
#define ACORAL_LIST_H

#define offsetof(TYPE, MEMBER) ((acoral_u32) &((TYPE *)0)->MEMBER)

///用于寻找给定的结构体成员所属的那个结构体
#define list_entry(ptr, type, member) ((type *)((acoral_8 *)ptr - offsetof(type,member)))

struct acoral_list {
	struct acoral_list *next, *prev;
};
typedef struct acoral_list acoral_list_t;

#define acoral_init_list(ptr) do { \
	(ptr)->next = (ptr); (ptr)->prev = (ptr); \
} while (0)

#define acoral_list_empty(head) ((head)->next==(head))

void acoral_list_add(acoral_list_t *new, acoral_list_t *head);
void acoral_list_add2_tail(acoral_list_t *new, acoral_list_t *head);
void acoral_list_del(acoral_list_t *entry);

#endif
