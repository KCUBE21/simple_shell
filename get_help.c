#include "shell.h"

/**
 * get_help - function that retrieves help messages according builtin
 * @datarel: the data structure
 * Return:  Return 0
*/
int get_help(data_shell *datarel)
{

	if (datarel->args[1] == 0)
		help_general();
	else if (_strcmp(datarel->args[1], "setenv") == 0)
		help_setvar();
	else if (_strcmp(datarel->args[1], "env") == 0)
		help_var();
	else if (_strcmp(datarel->args[1], "unsetenv") == 0)
		help_unsetvar();
	else if (_strcmp(datarel->args[1], "help") == 0)
		help();
	else if (_strcmp(datarel->args[1], "exit") == 0)
		help_exit();
	else if (_strcmp(datarel->args[1], "cd") == 0)
		help_cd();
	else if (_strcmp(datarel->args[1], "alias") == 0)
		help_alias();
	else
		write(STDERR_FILENO, datarel->args[0],
		      _strlen(datarel->args[0]));

	datarel->status = 0;
	return (1);
}
