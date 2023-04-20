#ifndef SHELL_H
#define SHELL_H
typedef struct acoral_shell_cmd_t acoral_shell_cmd_t;
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
