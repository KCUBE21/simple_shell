#include "shell.h"

/**
 * without_comment - it deletes comments from the input
 * @in: input string
 * Return: it  input without comments
 */

char *without_comment(char *in)
{
	int x, up_to;

	up_to = 0;
	for (x = 0; in[x]; x++)
	{
		if (in[x] == '#')
		{
			if (x == 0)
			{
				free(in);
				return (NULL);
			}

			if (in[x - 1] == ' ' || in[x - 1] == '\t' || in[x - 1] == ';')
				up_to = x;
		}
	}

	if (up_to != 0)
	{
		in = _realloc(in, x, up_to + 1);
		in[up_to] = '\0';
	}

	return (in);
}

/**
 * shell_loop - the Loop of shell
 * @datarel: the data relevant (av, input, args)
 *
 * Return: it returns nothing.
 */

void shell_loop(data_shell *datarel)
{
	int loop, i_eof;
	char *input;

	loop = 1;
	while (loop == 1)
	{
		write(STDIN_FILENO, "^-^ ", 4);
		input = read_line(&i_eof);
		if (i_eof != -1)
		{
			input = without_comment(input);
			if (input == NULL)
				continue;

			if (check_syntax_error(datarel, input) == 1)
			{
				datarel->status = 2;
				free(input);
				continue;
			}
			input = rep_var(input, datarel);
			loop = split_commands(datarel, input);
			datarel->counter += 1;
			free(input);
		}
		else
		{
			loop = 0;
			free(input);
		}
	}
}
