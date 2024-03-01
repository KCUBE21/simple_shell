#include "shell.h"

/**
 * copy_info - copies info to create
 * a new variable or alias
 * @name: the name (variable or alias)
 * @value: the value (variable or alias)
 * Return: returns new variableor alias.
 */
char *copy_info(char *name, char *value)
{
	char *new;
	int len_name, len_value, len;

	len_name = _strlen(name);
	len_value = _strlen(value);
	len = len_name + len_value + 2;
	new = malloc(sizeof(char) * (len));
	_strcpy(new, name);
	_strcat(new, "=");
	_strcat(new, value);
	_strcat(new, "\0");

	return (new);
}

/**
 * set_variable - sets an environment variable
 * @name: the name of the environment variable
 * @value: the value of the environment variable
 * @datarel: the data structure (environ)
 * Return: returns nothing
 */
void set_variable(char *name, char *value, data_shell *datarel)
{
	int i;
	char *var_variable, *name_variable;

	for (i = 0; datarel->_var[i]; i++)
	{
		var_variable = _strdup(datarel->_var[i]);
		name_variable = _strtok(var_variable, "=");
		if (_strcmp(name_variable, name) == 0)
		{
			free(datarel->_var[i]);
			datarel->_var[i] = copy_info(name_variable, value);
			free(var_variable);
			return;
		}
		free(var_variable);
	}

	datarel->_var = _reallocdp(datarel->_var, i, sizeof(char *) * (i + 2));
	datarel->_var[i] = copy_info(name, value);
	datarel->_var[i + 1] = NULL;
}

/**
 * _cmpvar - it compares env variables names
 * with the name passed.
 * @datarel: the data relevant (env name and env value)
 * Return: Always returns 1 on success.
 */

int _cmpvar(data_shell *datarel)
{

	if (datarel->args[1] == NULL || datarel->args[2] == NULL)
	{
		call_error(datarel, -1);
		return (1);
	}

	set_variable(datarel->args[1], datarel->args[2], datarel);

	return (1);
}

/**
 * _delvar - deletes a environment variable
 * @datarel: the data relevant (env name)
 * Return: Always return 1 on success.
 */
int _delvar(data_shell *datarel)
{
	char **realloc_var;
	char *var_variable, *name_variable;
	int i, j, k;

	if (datarel->args[1] == NULL)
	{
		call_error(datarel, -1);
		return (1);
	}
	k = -1;
	for (i = 0; datarel->_var[i]; i++)
	{
		var_variable = _strdup(datarel->_var[i]);
		name_variable = _strtok(var_variable, "=");
		if (_strcmp(name_variable, datarel->args[1]) == 0)
		{
			k = i;
		}
		free(var_variable);
	}
	if (k == -1)
	{
		call_error(datarel, -1);
		return (1);
	}
	realloc_var = malloc(sizeof(char *) * (i));
	for (i = j = 0; datarel->_var[i]; i++)
	{
		if (i != k)
		{
			realloc_var[j] = datarel->_var[i];
			j++;
		}
	}
	realloc_var[j] = NULL;
	free(datarel->_var[k]);
	free(datarel->_var);
	datarel->_var = realloc_var;
	return (1);
}
