#include "main.h"

/**
 * read_line - it reads the input string.
 *
 * @i_eof: it return value of getline function
 * Return: check input string
 */
char *read_line(int *i_eof)
{
	char *input = NULL;
	size_t bufsize = 0;

	*i_eof = getline(&input, &bufsize, stdin);

	return (input);
}
