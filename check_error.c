#include "shell.h"

/**
 * char_repeated - counts the repetitions of a char
 * @input: input string
 * @i: index
 * Return: always  repetitions
 */

int char_repeated(char *input, int i)
{
	if (*(input - 1) == *input)
		return (char_repeated(input - 1, i + 1));

	return (i);
}

/**
 * syn_error - finds syntax errors
 * @input: the input string
 * @i: the index
 * @last: the last char that was read
 * Return: returns index of error or 0 when there are no
 * errors
 */
int syn_error(char *input, int i, char last)
{
	int counts;

	counts = 0;
	if (*input == '\0')
		return (0);

	if (*input == ' ' || *input == '\t')
		return (syn_error(input + 1, i + 1, last));

	if (*input == ';')
		if (last == '|' || last == '&' || last == ';')
			return (i);

	if (*input == '|')
	{
		if (last == ';' || last == '&')
			return (i);

		if (last == '|')
		{
			counts = char_repeated(input, 0);
			if (counts == 0 || counts > 1)
				return (i);
		}
	}

	if (*input == '&')
	{
		if (last == ';' || last == '|')
			return (i);

		if (last == '&')
		{
			counts = char_repeated(input, 0);
			if (counts == 0 || counts > 1)
				return (i);
		}
	}

	return (syn_error(input + 1, i + 1, *input));
}

/**
 * first_char - finds index of the first char
 * @input: the input string
 * @i: the index
 * Return: Always return 1 if there is an error, 0 in other cases.
 */

int first_char(char *input, int *i)
{

	for (*i = 0; input[*i]; *i += 1)
	{
		if (input[*i] == ' ' || input[*i] == '\t')
			continue;

		if (input[*i] == ';' || input[*i] == '|' || input[*i] == '&')
			return (-1);

		break;
	}

	return (0);
}

/**
 * print_syn_error - prints when a syntax error is found
 * @datarel: the data structure
 * @input: the input string
 * @i: the index of the error
 * @bool: it control msg error
 * Return: returns nothing
 */

void print_syn_error(data_shell *datarel, char *input, int i, int bool)
{
	char *msg, *msg2, *msg3, *error, *counter;
	int length;

	if (input[i] == ';')
	{
		if (bool == 0)
			msg = (input[i + 1] == ';' ? ";;" : ";");
		else
			msg = (input[i - 1] == ';' ? ";;" : ";");
	}

	if (input[i] == '|')
		msg = (input[i + 1] == '|' ? "||" : "|");

	if (input[i] == '&')
		msg = (input[i + 1] == '&' ? "&&" : "&");

	msg2 = ": Syntax error: \"";
	msg3 = "\" unexpected\n";
	counter = hsh_itoa(datarel->counter);
	length = _strlen(datarel->av[0]) + _strlen(counter);
	length += _strlen(msg) + _strlen(msg2) + _strlen(msg3) + 2;

	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(counter);
		return;
	}
	_strcpy(error, datarel->av[0]);
	_strcat(error, ": ");
	_strcat(error, counter);
	_strcat(error, msg2);
	_strcat(error, msg);
	_strcat(error, msg3);
	_strcat(error, "\0");

	write(STDERR_FILENO, error, length);
	free(error);
	free(counter);
}

/**
 * check_syn_error - intermediate function to
 * find and print a syntax error
 * @datarel: the data structure
 * @input: the input string
 * Return: Always return 1 if there is an error. 0 in other case
 */
int check_syn_error(data_shell *datarel, char *input)
{
	int begin = 0;
	int f_char = 0;
	int i = 0;

	f_char = first_char(input, &begin);
	if (f_char == -1)
	{
		print_syn_error(datarel, input, begin, 0);
		return (1);
	}

	i = syn_error(input + begin, 0, *(input + begin));
	if (i != 0)
	{
		print_syn_error(datarel, input, begin + i, 1);
		return (1);
	}

	return (0);
}
