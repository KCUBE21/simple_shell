#ifndef _SHELL_H
#define _SHELL_H

#include <unistd.h>

typedef struct info_t {
	int readfd;
	char **argv;
	int status;
	int err_num;
	int argc;
	void *history;
	void *alias;
	int cmd_buf_type;
	int histcount;
	int linecount_flag;
	char **cmd_buf;




} info_t;

int check_interactive(info_t *info);
int is_delimiter(char c, char *delim);
int _isalpha_custom(int c);
int _atoi_custom(char *s);

int my_exit(info_t *info);
int my_cd(info_t *info);
int my_help(info_t *info);

int _erratoi(const char *s);
void print_error(info_t *info, const char *message);
char *_getenv(info_t *info, const char *name);
void _setenv(info_t *info, const char *name, const char *value);
int _strcmp(const char *s1, const char *s2);
void _puts(const char *str);
void _putchar(char c);
void _eputs(const char *str);
void _eputchar(char c);

int my_history(info_t *info);
int unset_alias(info_t *info, char *str);
int set_alias(info_t *info, char *str);
int print_alias(list_t *node);
int my_alias(info_t *info);

int _erratoi(const char *s);
void print_error(info_t *info, const char *message);
char *_strchr(const char *s, int c);
int delete_node_at_index(void *head, unsigned int index);
unsigned int get_node_index(void *head, const char *str);
void *add_node_end(void **head, const char *str, int len);
list_t *node_starts_with(void *head, const char *str, char c);
void print_list(void *h);
void _puts(const char *str);
void _putchar(char c);









#endif /* CUSTOM_SHELL_H */

