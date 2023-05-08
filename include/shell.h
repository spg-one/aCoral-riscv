/**
 * @file shell.h
 * @author 王彬浩 (SPGGOGOGO@outlook.com)
 * @brief kernel层，定时器相关头文件
 * @version 1.0
 * @date 2022-07-20
 * @copyright Copyright (c) 2023
 * @revisionHistory 
 *  <table> 
 *   <tr><th> 版本 <th>作者 <th>日期 <th>修改内容 
 *   <tr><td> 0.1 <td>jivin <td>2010-03-08 <td>Created 
 *   <tr><td> 1.0 <td>王彬浩 <td> 2022-07-20 <td>Standardized 
 *  </table>
 */


#ifndef SHELL_H
#define SHELL_H

enum parse_state {
	PS_WHITESPACE,
	PS_TOKEN,
	PS_STRING,
	PS_ESCAPE
};

typedef struct acoral_shell_cmd_t acoral_shell_cmd_t;

/**
 * @struct acoral_shell_cmd_t
 * @brief aCoral shell命令结构体
 * 
 */
struct acoral_shell_cmd_t{
	char *name;
	void (*exe)(int argc,const char **);
	char *comment;
	acoral_shell_cmd_t *next;
};

void acoral_shell_init(void);
void add_command(acoral_shell_cmd_t *cmd);
void acoral_shell_enter(void *args);
void cmd_init(void);
#endif
