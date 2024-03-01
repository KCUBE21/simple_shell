#include "shell.h"

/**
 * exit_shell - exits the shell
 * @datarel: the data relevant (status and args)
 * Return: Always returns 0 on success.
 */
int exit_shell(data_shell *datarel)
{
	unsigned int ustatus;
	int is_digit;
	int str_len;
	int big_number;

	if (datarel->args[1] != NULL)
	{
		ustatus = _atoi(datarel->args[1]);
		is_digit = _isnum(datarel->args[1]);
		str_len = _strlen(datarel->args[1]);
		big_number = ustatus > (unsigned int)INT_MAX;
		if (!is_digit || str_len > 10 || big_number)
		{
			call_error(datarel, 2);
			datarel->status = 2;
			return (1);
		}
		datarel->status = (ustatus % 256);
	}
	return (0);
}
