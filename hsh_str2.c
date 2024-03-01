#include "shell.h"

/**
 * _strdup - duplicates str in the heap memory.
 * @s: the Type char pointer str
 * Return: the duplicated str
 */

char *_strdup(const char *s)
{
	char *new;
	size_t len;

	len = _strlen(s);
	new = malloc(sizeof(char) * (len + 1));
	if (new == NULL)
		return (NULL);
	_memcpy(new, s, len + 1);
	return (new);
}

/**
 * _strlen - it Returns the lenght of a string.
 * @s: the Type char pointer
 * Return: Always retrun 0.
 */
int _strlen(const char *s)
{
	int len;

	for (len = 0; s[len] != 0; len++)
	{
	}
	return (len);
}

/**
 * cmp_chars - it compare chars of strings
 * @str: the input string.
 * @delim: the delimiter.
 *
 * Return: Returns 1 if equal, 0 if not.
 */

int cmp_chars(char str[], const char *delim)
{
	unsigned int i, j, k;

	for (i = 0, k = 0; str[i]; i++)
	{
		for (j = 0; delim[j]; j++)
		{
			if (str[i] == delim[j])
			{
				k++;
				break;
			}
		}
	}
	if (i == k)
		return (1);
	return (0);
}

/**
 * _strtok - it splits a string by some delimiter.
 * @str: the input string.
 * @delim: the delimiter.
 * Return: the string splited.
 */

char *_strtok(char str[], const char *delim)
{
	static char *splitted, *str_end;
	char *str_start;
	unsigned int i, bool;

	if (str != NULL)
	{
		if (cmp_chars(str, delim))
			return (NULL);
		splitted = str; /*it Store first address*/
		i = _strlen(str);
		str_end = &str[i]; /*it Store last address*/
	}
	str_start = splitted;
	if (str_start == str_end) /*it Reach end*/
		return (NULL);

	for (bool = 0; *splitted; splitted++)
	{
		/*Breaking loop to find the next token*/
		if (splitted != str_start)
			if (*splitted && *(splitted - 1) == '\0')
				break;
		/*it Replace delimiter for null char*/
		for (i = 0; delim[i]; i++)
		{
			if (*splitted == delim[i])
			{
				*splitted = '\0';
				if (splitted == str_start)
					str_start++;
				break;
			}
		}
		if (bool == 0 && *splitted) /*Str != Delim*/
			bool = 1;
	}
	if (bool == 0) /*Str == Delim*/
		return (NULL);
	return (str_start);
}


/**
 * _isnum - defines if string passed is a number
 * @s: the input string
 * Return: Returns 1 if string is a number. 0 in other case.
 */

int _isnum(const char *s)
{
	unsigned int x;

	for (x = 0; s[x]; x++)
	{
		if (s[x] < 48 || s[x] > 57)
			return (0);
	}
	return (1);
}

