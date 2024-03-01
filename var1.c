
#include "shell.h"

/**
 * cmp_var_name - compares env variables names
 * with the name passed.
 * @nameenv: name of the environment variable
 * @name: the name passed
 * Return: returns 0 if not equa, another value if they are.
 */
int cmp_var_name(const char *nameenv, const char *name)
{
	int x;

	for (x = 0; nameenv[x] != '='; x++)
	{
		if (nameenv[x] != name[x])
		{
			return (0);
		}
	}

	return (x + 1);
}

/**
 * _getvar - gets an variable
 * @name: the name of the variable
 * @_var: the environment variable
 * Return: returns value of the environment variable if found.
 * returns NULL in other case.
 */

char *_getvar(const char *name, char **_var)
{
	char *ptr_variable;
	int x, mov;

	/* It Initialize ptr_variable value */
	ptr_variable = NULL;
	mov = 0;
	/* It Compare all environment variables */
	/* It environ is declared in the header file */
	for (x = 0; _var[x]; x++)
	{
		/* name and env are equal */
		mov = cmp_var_name(_var[x], name);
		if (mov)
		{
			ptr_variable = _var[x];
			break;
		}
	}

	return (ptr_variable + mov);
}

/**
 * _variable - it prints the evironment variables
 * @datarel: the data relevant.
 * Return: Always return 1 on success.
 */

int _variable(data_shell *datarel)
{
	int x, j;

	for (x = 0; datarel->_var[x]; x++)
	{

		for (j = 0; datarel->_var[x][j]; j++)
			;

		write(STDOUT_FILENO, datarel->_var[x], j);
		write(STDOUT_FILENO, "\n", 1);
	}
	datarel->status = 0;

	return (1);
}
