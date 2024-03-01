#include "shell.h"

/**
 * cd_par - changes directory to the parent directory
 * @datarel: data that is relevant
 * Return: returns nothing
 */
void cd_par(data_shell *datarel)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_strtok_pwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);
	set_variable("OLDPWD", cp_pwd, datarel);
	dir = datarel->args[1];
	if (_strcmp(".", dir) == 0)
	{
		set_variable("PWD", cp_pwd, datarel);
		free(cp_pwd);
		return;
	}
	if (_strcmp("/", cp_pwd) == 0)
	{
		free(cp_pwd);
		return;
	}
	cp_strtok_pwd = cp_pwd;
	rev_str(cp_strtok_pwd);
	cp_strtok_pwd = _strtok(cp_strtok_pwd, "/");
	if (cp_strtok_pwd != NULL)
	{
		cp_strtok_pwd = _strtok(NULL, "\0");

		if (cp_strtok_pwd != NULL)
			rev_str(cp_strtok_pwd);
	}
	if (cp_strtok_pwd != NULL)
	{
		chdir(cp_strtok_pwd);
		set_variable("PWD", cp_strtok_pwd, datarel);
	}
	else
	{
		chdir("/");
		set_variable("PWD", "/", datarel);
	}
	datarel->status = 0;
	free(cp_pwd);
}

/**
 * cd_to - changes directory to a directory given
 * by the user
 * @datarel: the data that is relevant
 * Return: returns nothing
 */
void cd_to(data_shell *datarel)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_dir;

	getcwd(pwd, sizeof(pwd));

	dir = datarel->args[1];
	if (chdir(dir) == -1)
	{
		call_error(datarel, 2);
		return;
	}

	cp_pwd = _strdup(pwd);
	set_variable("OLDPWD", cp_pwd, datarel);

	cp_dir = _strdup(dir);
	set_variable("PWD", cp_dir, datarel);

	free(cp_pwd);
	free(cp_dir);

	datarel->status = 0;

	chdir(dir);
}

/**
 * cd_previous - changes directory to the previous directory
 * @datarel: data that is relevant
 * Return: return nothing
 */

void cd_previous(data_shell *datarel)
{
	char pwd[PATH_MAX];
	char *p_pwd, *p_oldpwd, *cp_pwd, *cp_oldpwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);

	p_oldpwd = _getvar("OLDPWD", datarel->_var);

	if (p_oldpwd == NULL)
		cp_oldpwd = cp_pwd;
	else
		cp_oldpwd = _strdup(p_oldpwd);

	set_variable("OLDPWD", cp_pwd, datarel);

	if (chdir(cp_oldpwd) == -1)
		set_variable("PWD", cp_pwd, datarel);
	else
		set_variable("PWD", cp_oldpwd, datarel);

	p_pwd = _getvar("PWD", datarel->_var);

	write(STDOUT_FILENO, p_pwd, _strlen(p_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(cp_pwd);
	if (p_oldpwd)
		free(cp_oldpwd);

	datarel->status = 0;

	chdir(p_pwd);
}

/**
 * cd_home - changes directory to home directory
 * @datarel: data that is relevant
 * Return: returns nothing
 */
void cd_home(data_shell *datarel)
{
	char *p_pwd, *home;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	p_pwd = _strdup(pwd);

	home = _getvar("HOME", datarel->_var);

	if (home == NULL)
	{
		set_variable("OLDPWD", p_pwd, datarel);
		free(p_pwd);
		return;
	}

	if (chdir(home) == -1)
	{
		call_error(datarel, 2);
		free(p_pwd);
		return;
	}

	set_variable("OLDPWD", p_pwd, datarel);
	set_variable("PWD", home, datarel);
	free(p_pwd);
	datarel->status = 0;
}
