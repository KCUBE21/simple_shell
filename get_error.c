#include "shell.h"

/**
 * call_error - calls the error according the builtin, syntax or permission
 * @datarel: the data structure that contains arguments
 * @eval: the error value
 * Return: return error
 */
int call_error(data_shell *datarel, int eval)
{
	char *error;

	switch (eval)
	{
	case -1:
		error = error_env(datarel);
		break;
	case 126:
		error = error_path(datarel);
		break;
	case 127:
		error = error_not_found(datarel);
		break;
	case 2:
		if (_strcmp("exit", datarel->args[0]) == 0)
			error = error_exit_shell(datarel);
		else if (_strcmp("cd", datarel->args[0]) == 0)
			error = error_get_cd(datarel);
		break;
	}

	if (error)
	{
		write(STDERR_FILENO, error, _strlen(error));
		free(error);
	}

	datarel->status = eval;
	return (eval);
}
