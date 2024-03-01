#include "shell.h"

/**
 * cd_shell - changes current directory
 * @datarel: data that is relevant
 * Return: returns 1 on success
 */
int cd_shell(data_shell *datarel)
{
	char *dir;
	int ishome, ishome2, isddash;

	dir = datarel->args[1];

	if (dir != NULL)
	{
		ishome = _strcmp("$HOME", dir);
		ishome2 = _strcmp("~", dir);
		isddash = _strcmp("--", dir);
	}

	if (dir == NULL || !ishome || !ishome2 || !isddash)
	{
		cd_to_home(datarel);
		return (1);
	}

	if (_strcmp("-", dir) == 0)
	{
		cd_previous(datarel);
		return (1);
	}

	if (_strcmp(".", dir) == 0 || _strcmp("..", dir) == 0)
	{
		cd_dot(datarel);
		return (1);
	}

	cd_to(datarel);

	return (1);
}
