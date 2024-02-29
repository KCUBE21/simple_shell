#ifndef _SHELL_H
#define _SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

#define READ_BUF_SIZE 1024
#define BUF_FLUSH '\n'

/* Struct for shell information */
typedef struct
{
	char **arg;
	char ***cmd_buf;
	int linecount_flag;
	int histcount;
	int readfd;
	int cmd_buf_type;
} info_t;

/* Function prototypes */
ssize_t bufferInput(info_t *info, char **buffer, size_t *length);
ssize_t getInput(info_t *info);
ssize_t readBuffer(info_t *info, char *buffer, size_t *i);
int customGetline(info_t *info, char **ptr, size_t *length);
void handleSIGINT(int signal_number);

#endif

