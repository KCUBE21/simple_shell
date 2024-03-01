#include "shell.h"

/**
 * free_data - it frees data structure
 * @datarel:the  data structure
 * Return: it returns nothing
 */

void free_data(data_shell *datarel)
{
	unsigned int x;

	for (x = 0; datarel->_environ[x]; x++)
	{
		free(datarel->_environ[x]);
	}

	free(datarel->_environ);
	free(datarel->pid);
}

/**
 * set_data - it initialize data structure
 * @datarel: the data struture
 * @av: the argument vector
 * Return: it returns nothing
 */

void set_data(data_shell *datarel, char **av)
{
	unsigned int x;

	datarel->av = av;
	datarel->input = NULL;
	datarel->args = NULL;
	datarel->status = 0;
	datarel->counter = 1;

	for (x = 0; environ[x]; x++)
		;
	datarel->_environ = malloc(sizeof(char *) * (x + 1));

	for (x = 0; environ[x]; x++)
	{
		datarel->_environ[x] = _strdup(environ[x]);
	}

	datarel->_environ[x] = NULL;
	datarel->pid = hsh_itoa(getpid());
}

/**
 * main - the main program
 * @ac: the argument count
 * @av: the argument vector
 * Return: 0 = success
 */

int main(int ac, char **av)
{
	data_shell datarel;
	(void) ac;

	signal(SIGINT, get_sigint);
	set_data(&datarel, av);
	shell_loop(&datarel);
	free_data(&datarel);
	if (datarel.status < 0)
		return (255);
	return (datarel.status);
}
