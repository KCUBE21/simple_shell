#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>

#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"


/* It Points to an array of pointers to strings called the "environment" */
extern char **environ;


/**
 * struct data - the struct that contains all relevant data on runtime
 * @av: argument vector
 * @input: the command line written by the user
 * @args: the tokens of the command line
 * @status: the last status of the shell
 * @counter: the lines counter
 * @_environ: the environment variable
 * @pid: the process ID of the shell
 */
typedef struct data
{
	char **av;
	char *input;
	char **args;
	int status;
	int counter;
	char **_environ;
	char *pid;
} data_shell;

/**
 * struct sepa_list_s - the single linked list
 * @separator: ; | &
 * @next: next node
 * Description: the single linked list to store separators
 */
typedef struct sepa_list_s
{
	char separator;
	struct sepa_list_s *next;
} sepa_list;

/**
 * struct line_list_s - single linked list
 * @line: command line
 * @next: next node
 * Description: single linked list to store command lines
 */
typedef struct line_list_s
{
	char *line;
	struct line_list_s *next;
} line_list;

/**
 * struct builtin_s - the Builtin struct for command args.
 * @name:  name of the command builtin i.e cd, exit, env
 * @f: the data type pointer function.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(data_shell *datash);
} builtin_t;


/**
 * struct r_var_list - it is a single linked list
 * @len_var: length of variable
 * @val: value of variable
 * @len_val: length of value
 * @next: the next node
 * Description: the single linked list to store variables
 */
typedef struct r_var_list
{
	int len_var;
	char *val;
	int len_val;
	struct r_var_list *next;
} r_var;


/* hsh_lists.c  */
sepa_list *add_sepa_node_end(sepa_list **head, char sepa);
void free_sepa_list(sepa_list **head);
line_list *add_line_node_end(line_list **head, char *line);
void free_line_list(line_list **head);

/* hsh_lists2.c */
r_var *add_rvar_node(r_var **head, int lvar, char *var, int lval);
void free_rvar_list(r_var **head);

/* memory.c */
void _memcpy(void *newptr, const void *ptr, unsigned int size);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size);

/* shell_loop.c */
char *without_comment(char *in);
void shell_loop(data_shell *datash);

/* read_line.c */
char *read_line(int *i_eof);

/* exec_line */
int exec_line(data_shell *datash);

/* get_sigint.c */
void get_sigint(int sig);

/* hsh_str.c */
char *_strcat(char *dest, const char *src);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);

/* hsh_str3.c */
void rev_string(char *s);

/* hsh_str2.c */
char *_strdup(const char *s);
int _strlen(const char *s);
int cmp_chars(char str[], const char *delim);
char *_strtok(char str[], const char *delim);
int _isdigit(const char *s);

/* check_error.c */
int repeated_char(char *input, int i);
int error_sep_op(char *input, int i, char last);
int first_char(char *input, int *i);
void print_syntax_error(data_shell *datash, char *input, int i, int bool);
int check_syntax_error(data_shell *datash, char *input);

/* split.c */
char *swap_char(char *input, int bool);
void add_nodes(sepa_list **head_s, line_list **head_l, char *input);
void go_next(sepa_list **list_s, line_list **list_l, data_shell *datash);
int split_commands(data_shell *datash, char *input);
char **split_line(char *input);

/* var.c */
void check_env(r_var **h, char *in, data_shell *data);
int check_vars(r_var **h, char *in, char *st, data_shell *data);
char *replaced_input(r_var **head, char *input, char *new_input, int nlen);
char *rep_var(char *input, data_shell *datash);

/* cmd_exec.c */
int is_cdir(char *path, int *i);
char *_which(char *cmd, char **_environ);
int is_executable(data_shell *datash);
int check_error_cmd(char *dir, data_shell *datash);
int cmd_exec(data_shell *datash);

/* env1.c */
char *_getenv(const char *name, char **_environ);
int _env(data_shell *datash);

/* env2.c */
char *copy_info(char *name, char *value);
void set_env(char *name, char *value, data_shell *datash);
int _setenv(data_shell *datash);
int _unsetenv(data_shell *datash);

/* cd.c */
void cd_dot(data_shell *datash);
void cd_to(data_shell *datash);
void cd_previous(data_shell *datash);
void cd_to_home(data_shell *datash);

/* cd_shell.c */
int cd_shell(data_shell *datash);

/* get_builtin */
int (*get_builtin(char *cmd))(data_shell *datash);

/* _exit.c */
int exit_shell(data_shell *datash);

/* hsh_stdlib.c */
int get_len(int n);
char *hsh_itoa(int n);
int _atoi(char *s);

/* hsh_error1.c */
char *strcat_cd(data_shell *, char *, char *, char *);
char *error_get_cd(data_shell *datash);
char *error_not_found(data_shell *datash);
char *error_exit_shell(data_shell *datash);

/* hsh_error2.c */
char *error_get_alias(char **args);
char *error_env(data_shell *datash);
char *error_syntax(char **args);
char *error_permission(char **args);
char *error_path_126(data_shell *datash);

/* get_error.c */
int get_error(data_shell *datash, int eval);

/* hsh_help.c */
void hsh_help_env(void);
void hsh_help_setenv(void);
void hsh_help_unsetenv(void);
void hsh_help_general(void);
void hsh_help_exit(void);

/* hsh_help2.c */
void hsh_help(void);
void hsh_help_alias(void);
void hsh_help_cd(void);

/* get_help */
int get_help(data_shell *datash);

/* read_line.c */
char *read_line(int *i_eof);

/* get_line.c */
void bring_line(char **lineptr, size_t *n, char *buffer, size_t j);
ssize_t get_line(char **lineptr, size_t *n, FILE *stream);

#endif
