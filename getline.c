#include "shell.h"

/**
 *bufferInput - buffers chained commands
 *@info: parameter struct
 *@buffer: address of buffer
 *@length: address of length variable
 *
 *Return: bytes read
 */
ssize_t bufferInput(info_t *info, char **buffer, size_t *length)
{
	ssize_t bytes_read = 0;
	size_t length_pending = 0;

	if (!*length)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, handleSIGINT);

#if USE_GETLINE
		bytes_read = getline(buffer, &length_pending, stdin);
#else
		bytes_read = customGetline(info, buffer, &length_pending);
#endif

		if (bytes_read > 0)
		{
			if ((*buffer)[bytes_read - 1] == '\n')
			{
				(*buffer)[bytes_read - 1] = '\0';
				bytes_read--;
			}
			info->linecount_flag = 1;
			removeComments(*buffer);
			buildHistoryList(info, *buffer, info->histcount++);
			*length = bytes_read;
			info->cmd_buf = buffer;
		}
	}
	return (bytes_read);
}

/**
 *getInput - gets a line minus the newline
 *@info: parameter struct
 *
 *Return: bytes read
 */
ssize_t getInput(info_t *info)
{
	static char *buffer;
	static size_t i, j, length;
	ssize_t bytes_read = 0;
	char **buffer_ptr = &(info->arg), *p;

	putchar(BUF_FLUSH);
	bytes_read = bufferInput(info, &buffer, &length);

	if (bytes_read == -1)
		return (-1);

	if (length)
	{
		j = i;
		p = buffer + i;
		checkChain(info, buffer, &j, i, length);

		while (j < length)
		{
			if (isChain(info, buffer, &j))
				break;
			j++;
		}

		i = j + 1;

		if (i >= length)
		{
			i = length = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buffer_ptr = p;
		return (strlen(p));
	}

	*buffer_ptr = buffer;
	return (bytes_read);
}

/**
 *readBuffer - reads a buffer
 *@info: parameter struct
 *@buffer: buffer
 *@i: size
 *
 *Return: r
 */
ssize_t readBuffer(info_t *info, char *buffer, size_t *i)
{
	ssize_t bytes_read = 0;

	if (*i)
		return (0);

	bytes_read = read(info->readfd, buffer, READ_BUF_SIZE);

	if (bytes_read >= 0)
		*i = bytes_read;

	return (bytes_read);
}

/**
 *customGetline - gets the next line of input from STDIN
 *@info: parameter struct
 *@ptr: address of pointer to buffer, preallocated or NULL
 *@length: size of preallocated ptr buffer if not NULL
 *
 *Return: s
 */
int customGetline(info_t *info, char **ptr, size_t *length)
{
	static char buffer[READ_BUF_SIZE];
	static size_t i, length_pending;
	size_t k;
	ssize_t bytes_read = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;

	if (i == length_pending)
		i = length_pending = 0;

	bytes_read = readBuffer(info, buffer, &length_pending);

	if (bytes_read == -1 || (bytes_read == 0 && length_pending == 0))
		return (-1);

	c = strchr(buffer + i, '\n');
	k = c ? 1 + (unsigned int)(c - buffer) : length_pending;
	new_p = realloc(p, s ? s + k : k + 1);

	if (!new_p)
		return (p ? (free(p), -1) : -1);

	if (s)
		strncat(new_p, buffer + i, k - i);
	else
		strncpy(new_p, buffer + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;

	*ptr = p;
	return (s);
}

/**
 *handleSIGINT - blocks ctrl-C
 *@signal_number: the signal number
 *
 *Return: void
 */
void handleSIGINT(__attribute__((unused)) int signal_number)
{
	puts("\n$ ");
	putchar(BUF_FLUSH);
}
