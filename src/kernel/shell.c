#include<acoral.h>
#include "shell.h"
#include "thread.h"
#include <stdio.h>
#include <string.h>

#define BUF_SIZE 128
#define MAX_ARGS_NUM 8
acoral_shell_cmd_t *head_cmd,*tail_cmd;
enum parse_state {
	PS_WHITESPACE,
	PS_TOKEN,
	PS_STRING,
	PS_ESCAPE
};

void parse_args(acoral_char *argstr, acoral_32 *argc_p, acoral_char **argv, acoral_char** resid,enum parse_state *stacked)
{
	acoral_32 argc = 0;
	acoral_char c;
	enum parse_state newState;
	enum parse_state stacked_state=*stacked;
	enum parse_state lastState = PS_WHITESPACE;

	while ((c = *argstr) != 0&&argc<MAX_ARGS_NUM) {

		if (c == ';' && lastState != PS_STRING && lastState != PS_ESCAPE)
			break;

		if (lastState == PS_ESCAPE) {
			newState = stacked_state;
		} else if (lastState == PS_STRING) {
			if (c == '"') {
				newState = PS_WHITESPACE;
				*argstr = 0;
			} else {
				newState = PS_STRING;
			}
		} else if ((c == ' ') || (c == '\t')) {
			*argstr = 0;
			newState = PS_WHITESPACE;
		} else if (c == '"') {
			newState = PS_STRING;
			*argstr++ = 0;
			argv[argc++] = argstr;
		} else if (c == '\\') {
			stacked_state = lastState;
			newState = PS_ESCAPE;
		} else {
			if (lastState == PS_WHITESPACE) {
				argv[argc++] = argstr;
			}
			newState = PS_TOKEN;
		}

		lastState = newState;
		argstr++;
	}

	argv[argc] = NULL;
	if (argc_p != NULL)
		*argc_p = argc;

	if (*argstr == ';') {
		*argstr++ = '\0';
	}
	*resid = argstr;
	*stacked=stacked_state;
}

void add_command(acoral_shell_cmd_t *cmd)
{
	if (head_cmd == NULL) {
		head_cmd = tail_cmd = cmd;
	} else {
		tail_cmd->next = cmd;
		tail_cmd = cmd;
	}
}

acoral_shell_cmd_t *find_cmd(const acoral_char *cmdname)
{
	acoral_shell_cmd_t *curr;
	curr =head_cmd;
	while(curr != NULL) {
		if (strcmp(curr->name, cmdname) == 0)
			return curr;
		curr = curr->next;
	}
	return NULL;
}

void execmd(acoral_32 argc,const acoral_char **argv)
{
	acoral_shell_cmd_t *cmd = find_cmd(argv[0]);
	if (cmd == NULL) {
		printf("Could not found '%s' command\r\n", argv[0]);
		printf("you can type 'help'\r\n"); 
		return;
	}
	cmd->exe(argc, argv);
}


void cmd_exe(acoral_char *buf){
	acoral_32 argc;
	acoral_char *argv[MAX_ARGS_NUM];
	acoral_char *resid;
	enum parse_state stacked_state;
	while (*buf) {
		memset(argv, 0, sizeof(argv));
		parse_args(buf, &argc, argv, &resid,&stacked_state);
		if (argc > 0)
			execmd(argc, (const acoral_char **)argv);//TODO 保留const？
		buf = resid;
	}	
}

#define SHELL_STACK_SIZE 1024
void acoral_shell_init(void){
	acoral_comm_policy_data_t data;
	head_cmd=NULL;
	tail_cmd=NULL;
	cmd_init();

	data.prio=ACORAL_TMP_PRIO;
	data.prio_type=ACORAL_ABSOLUTE_PRIO;
	acoral_create_thread(acoral_shell_enter,SHELL_STACK_SIZE,(void *)acoral_cur_thread->console_id,"shell",NULL,ACORAL_SCHED_POLICY_COMM,&data);
}


void acoral_shell_enter(void *args){
	acoral_char *cmd_buf;
	acoral_set_thread_console((acoral_id)args);
	if(acoral_cur_thread->console_id<0){
		printf("The thread have no Console\n");
		return;
	}
	cmd_buf=acoral_malloc(sizeof(BUF_SIZE));
	while(1){
		printf("\r\n");
		printf("aCoral:>");
		if(cmd_buf[0])
			cmd_exe(cmd_buf);
	}
}
