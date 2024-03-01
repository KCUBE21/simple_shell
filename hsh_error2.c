#include "shell.h"

/**
 * error_env - the error message for env in get_env.
 * @datarel: the data relevant (counter, arguments)
 * Return: return error message.
 */
char *error_env(data_shell *datarel)
{
	int length;
	char *error;
	char *ver_str;
	char *msg;

	ver_str = hsh_itoa(datarel->counter);
	msg = ": Unable to add/remove from environment\n";
	length = _strlen(datarel->av[0]) + _strlen(ver_str);
	length += _strlen(datarel->args[0]) + _strlen(msg) + 4;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(error);
		free(ver_str);
		return (NULL);
	}

	_strcpy(error, datarel->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, datarel->args[0]);
	_strcat(error, msg);
	_strcat(error, "\0");
	free(ver_str);

	return (error);
}

/**
 * error_path - the error message for path and failure denied permission.
 * @datarel: the data relevant.
 * Return: The error string.
 */
char *error_path(data_shell *datarel)
{
	int length;
	char *ver_str;
	char *error;

	ver_str = hsh_itoa(datarel->counter);
	length = _strlen(datarel->av[0]) + _strlen(ver_str);
	length += _strlen(datarel->args[0]) + 24;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(error);
		free(ver_str);
		return (NULL);
	}
	_strcpy(error, datarel->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, datarel->args[0]);
	_strcat(error, ": Permission denied\n");
	_strcat(error, "\0");
	free(ver_str);
	return (error);
}
