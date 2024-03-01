#include "main.h"

/**
 * cmp_env_name - the compares env variables names
 * with the name passed.
 * @nenv: the name of the environment variable
 * @name: the name passed
 * Return: Always returns 0 if are not equal. Another value if they are.
 */
int cmp_env_name(const char *nenv, const char *name)
{
	int x;

	for (x = 0; nenv[x] != '='; x++)
	{
		if (nenv[x] != name[x])
		{
			return (0);
		}
	}

	return (x + 1);
}

/**
 * _getenv - it get an environment variable
 * @name: the name of the environment variable
 * @_environ: the environment variable
 * Return: Always return value of the environment variable if is found.
 * In other case, returns NULL.
 */

char *_getenv(const char *name, char **_environ)
{
	char *ptr_env;
	int x, mov;

	/* It Initialize ptr_env value */
	ptr_env = NULL;
	mov = 0;
	/* It Compare all environment variables */
	/* It environ is declared in the header file */
	for (x = 0; _environ[x]; x++)
	{
		/* name and env are equal */
		mov = cmp_env_name(_environ[x], name);
		if (mov)
		{
			ptr_env = _environ[x];
			break;
		}
	}

	return (ptr_env + mov);
}

/**
 * _env - it prints the evironment variables
 * @datash: the data relevant.
 * Return: Always return 1 on success.
 */

int _env(data_shell *datash)
{
	int x, j;

	for (x = 0; datash->_environ[x]; x++)
	{

		for (j = 0; datash->_environ[x][j]; j++)
			;

		write(STDOUT_FILENO, datash->_environ[x], j);
		write(STDOUT_FILENO, "\n", 1);
	}
	datash->status = 0;

	return (1);
}
