#include "shell.h"

/**
 * ass_line - assigns the line var for get_line
 * @instr: the Buffer that store the input str
 * @buffer: the str that is been called to line
 * @n: the size of line
 * @j: the size of buffer
 * Return: returns nothing
 */
void ass_line(char **instr, size_t *n, char *buffer, size_t j)
{

	if (*instr == NULL)
	{
		if  (j > BUFSIZE)
			*n = j;

		else
			*n = BUFSIZE;
		*instr = buffer;
	}
	else if (*n < j)
	{
		if (j > BUFSIZE)
			*n = j;
		else
			*n = BUFSIZE;
		*instr = buffer;
	}
	else
	{
		_strcpy(*instr, buffer);
		free(buffer);
	}
}
/**
 * get_line - It Read inpt from stream
 * @instr: the buffer that stores the input
 * @n: the size of instr
 * @stream: The stream to read from
 * Return: Returns The number of bytes
 */
ssize_t get_line(char **instr, size_t *n, FILE *stream)
{
	int i;
	static ssize_t input;
	ssize_t retval;
	char *buffer;
	char t = 'z';

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	buffer = malloc(sizeof(char) * BUFSIZE);
	if (buffer == 0)
		return (-1);
	while (t != '\n')
	{
		i = read(STDIN_FILENO, &t, 1);
		if (i == -1 || (i == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (i == 0 && input != 0)
		{
			input++;
			break;
		}
		if (input >= BUFSIZE)
			buffer = _realloc(buffer, input, input + 1);
		buffer[input] = t;
		input++;
	}
	buffer[input] = '\0';
	ass_line(instr, n, buffer, input);
	retval = input;
	if (i != 0)
		input = 0;
	return (retval);
}
