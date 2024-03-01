#include "shell.h"

/**
 * str_concat - concatenate two strings
 * @dest: the char pointer to the dest of the copied str
 * @src: the const char pointer the source of str
 * Return:  dest
 */

char *str_concat(char *dest, const char *src)
{
	int x;
	int j;

	for (x = 0; dest[x] != '\0'; x++)
		;

	for (j = 0; src[j] != '\0'; j++)
	{
		dest[x] = src[j];
		x++;
	}

	dest[x] = '\0';
	return (dest);
}

/**
 * *str_copy - it Copies the string pointed to by src.
 * @dest:  char pointer the dest of the copied str
 * @src:  char pointer the source of str
 * Return: dest.
 */

char *str_copy(char *dest, char *src)
{

	size_t a;

	for (a = 0; src[a] != '\0'; a++)
	{
		dest[a] = src[a];
	}
	dest[a] = '\0';

	return (dest);
}

/**
 * str_cmp - the Function that compares two strings.
 * @s1: the type str compared
 * @s2: the type str compared
 * Return: it returns  0.
 */
int str_cmp(char *s1, char *s2)
{
	int x;

	for (x = 0; s1[x] == s2[x] && s1[x]; x++)
		;

	if (s1[x] > s2[x])
		return (1);
	if (s1[x] < s2[x])
		return (-1);
	return (0);
}

/**
 * str_charr - it locates a character in a string,
 * @s: the string.
 * @c: the character.
 * Return:  pointer to the first occurrence of the character c.
 */
char *str_char(char *s, char c)
{
	unsigned int x = 0;

	for (; *(s + x) != '\0'; x++)
		if (*(s + x) == c)
			return (s + x);
	if (*(s + x) == c)
		return (s + x);
	return ('\0');
}

/**
 * sub_str - it gets the length of a prefix substring.
 * @s: the initial segment.
 * @accept: the  accepted bytes.
 * Return:  number of accepted bytes.
 */
int sub_str(char *s, char *accept)
{
	int x, j, bool;

	for (x = 0; *(s + x) != '\0'; x++)
	{
		bool = 1;
		for (j = 0; *(accept + j) != '\0'; j++)
		{
			if (*(s + x) == *(accept + j))
			{
				bool = 0;
				break;
			}
		}
		if (bool == 1)
			break;
	}
	return (x);
}
