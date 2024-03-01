#include "shell.h"

/**
 * is_currdir - it checks ":" if it is in the current directory.
 * @path: the type char pointer char.
 * @i: pointer to index.
 * Return: return 1 if the path is searchable in the cd, 0 if otherwise.
 */

int is_currdir(char *path, int *i)
{
	if (path[*i] == ':')
		return (1);

	while (path[*i] != ':' && path[*i])
	{
		*i += 1;
	}

	if (path[*i])
		*i += 1;

	return (0);
}

/**
 * which_cmd - it locates a command
 * @cmd: the command name
 * @_var: the environment variable
 * Return: return location of the command.
 */

char *which_cmd(char *cmd, char **_var)
{
	char *path, *ptr_path, *token_path, *dir;
	int len_dir, len_cmd, i;
	struct stat st;

	path = _getvar("PATH", _var);
	if (path)
	{
		ptr_path = _strdup(path);
		len_cmd = _strlen(cmd);
		token_path = _strtok(ptr_path, ":");
		i = 0;
		while (token_path != NULL)
		{
			if (is_currdir(path, &i))
				if (stat(cmd, &st) == 0)
					return (cmd);
			len_dir = _strlen(token_path);
			dir = malloc(len_dir + len_cmd + 2);
			_strcpy(dir, token_path);
			_strcat(dir, "/");
			_strcat(dir, cmd);
			_strcat(dir, "\0");
			if (stat(dir, &st) == 0)
			{
				free(ptr_path);
				return (dir);
			}
			free(dir);
			token_path = _strtok(NULL, ":");
		}
		free(ptr_path);
		if (stat(cmd, &st) == 0)
			return (cmd);
		return (NULL);
	}
	if (cmd[0] == '/')
		if (stat(cmd, &st) == 0)
			return (cmd);
	return (NULL);
}

/**
 * is_executable - it determines if is an executable
 * @datarel: the data structure
 * Return: returns 0 if is not an executable, other number if otherwise
 */

int is_executable(data_shell *datarel)
{
	struct stat st;
	int i;
	char *input;

	input = datarel->args[0];
	for (i = 0; input[i]; i++)
	{
		if (input[i] == '.')
		{
			if (input[i + 1] == '.')
				return (0);
			if (input[i + 1] == '/')
				continue;
			else
				break;
		}
		else if (input[i] == '/' && i != 0)
		{
			if (input[i + 1] == '.')
				continue;
			i++;
			break;
		}
		else
			break;
	}
	if (i == 0)
		return (0);

	if (stat(input + i, &st) == 0)
	{
		return (i);
	}
	call_error(datarel, 127);
	return (-1);
}

/**
 * error_cmd - it verifies if user has permissions to access
 * @dir: the destination directory
 * @datarel: the data structure
 * Return: return 1 if there is an error, 0 if not
 */

int error_cmd(char *dir, data_shell *datarel)
{
	if (dir == NULL)
	{
		call_error(datarel, 127);
		return (1);
	}

	if (_strcmp(datarel->args[0], dir) != 0)
	{
		if (access(dir, X_OK) == -1)
		{
			call_error(datarel, 126);
			free(dir);
			return (1);
		}
		free(dir);
	}
	else
	{
		if (access(datarel->args[0], X_OK) == -1)
		{
			call_error(datarel, 126);
			return (1);
		}
	}

	return (0);
}

/**
 * cmd_exec - it executes command lines
 * @datarel: the data relevant (args and input)
 * Return: Always return 1 on success.
 */

int cmd_exec(data_shell *datarel)
{
	pid_t pd;
	pid_t wpd;
	int state;
	int exec;
	char *dir;
	(void) wpd;

	exec = is_executable(datarel);
	if (exec == -1)
		return (1);
	if (exec == 0)
	{
		dir = which_cmd(datarel->args[0], datarel->_var);
		if (error_cmd(dir, datarel) == 1)
			return (1);
	}

	pd = fork();
	if (pd == 0)
	{
		if (exec == 0)
			dir = which_cmd(datarel->args[0], datarel->_var);
		else
			dir = datarel->args[0];
		execve(dir + exec, datarel->args, datarel->_var);
	}
	else if (pd < 0)
	{
		perror(datarel->av[0]);
		return (1);
	}
	else
	{
		do {
			wpd = waitpid(pd, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}

	datarel->status = state / 256;
	return (1);
}
