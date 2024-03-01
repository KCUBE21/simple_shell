#include "shell.h"

/**
 * strcat - it function that concatenates the message for cd error
 * @datarel: the data relevant (directory)
 * @msg: the message to print
 * @error: the output message
 * @ver_str: the counter lines
 * Return: AAlways returns error message
 */
char *strcat(data_shell *datarel, char *msg, char *error, char *ver_str)
{
	char *illegal_flag;

	_strcpy(error, datarel->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, datarel->args[0]);
	_strcat(error, msg);
	if (datarel->args[1][0] == '-')
	{
		illegal_flag = malloc(3);
		illegal_flag[0] = '-';
		illegal_flag[1] = datarel->args[1][1];
		illegal_flag[2] = '\0';
		_strcat(error, illegal_flag);
		free(illegal_flag);
	}
	else
	{
		_strcat(error, datarel->args[1]);
	}

	_strcat(error, "\n");
	_strcat(error, "\0");
	return (error);
}

/**
 * error_get_cd - it error message for cd command in get_cd
 * @datarel: the data relevant (directory)
 * Return: Always Error message
 */
char *error_get_cd(data_shell *datarel)
{
	int length, len_id;
	char *error, *ver_str, *msg;

	ver_str = hsh_itoa(datarel->counter);
	if (datarel->args[1][0] == '-')
	{
		msg = ": Illegal option ";
		len_id = 2;
	}
	else
	{
		msg = ": can't cd to ";
		len_id = _strlen(datarel->args[1]);
	}

	length = _strlen(datarel->av[0]) + _strlen(datarel->args[0]);
	length += _strlen(ver_str) + _strlen(msg) + len_id + 5;
	error = malloc(sizeof(char) * (length + 1));

	if (error == 0)
	{
		free(ver_str);
		return (NULL);
	}

	error = strcat(datarel, msg, error, ver_str);

	free(ver_str);

	return (error);
}

/**
 * error_not_found - generic error message for command not found
 * @datarel: the data relevant (counter, arguments)
 * Return: return Error message
 */
char *error_not_found(data_shell *datarel)
{
	int length;
	char *error;
	char *ver_str;

	ver_str = hsh_itoa(datarel->counter);
	length = _strlen(datarel->av[0]) + _strlen(ver_str);
	length += _strlen(datarel->args[0]) + 16;
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
	_strcat(error, ": not found\n");
	_strcat(error, "\0");
	free(ver_str);
	return (error);
}

/**
 * error_exit_shell - generic error message for exit in get_exit
 * @datarel: the data relevant (counter, arguments)
 * Return: return Error message
 */
char *error_exit_shell(data_shell *datarel)
{
	int length;
	char *error;
	char *ver_str;

	ver_str = hsh_itoa(datarel->counter);
	length = _strlen(datarel->av[0]) + _strlen(ver_str);
	length += _strlen(datarel->args[0]) + _strlen(datarel->args[1]) + 23;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(ver_str);
		return (NULL);
	}
	_strcpy(error, datarel->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, datarel->args[0]);
	_strcat(error, ": Illegal number: ");
	_strcat(error, datarel->args[1]);
	_strcat(error, "\n\0");
	free(ver_str);

	return (error);
}
