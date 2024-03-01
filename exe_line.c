#include "shell.h"

/**
 * buil_cmd - it finds builtins and commands
 *
 * @datarel: the data relevant (args)
 * Return: it returns  1 on success.
 */

int buil_cmd(data_shell *datarel)
{
	int (*builtin)(data_shell *datarel);

	if (datarel->args[0] == NULL)
		return (1);

	builtin = pass_builtin(datarel->args[0]);

	if (builtin != NULL)
		return (builtin(datarel));

	return (cmd_exec(datarel));
}
