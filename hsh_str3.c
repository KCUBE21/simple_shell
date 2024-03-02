#include "main.h"

/**
 * rev_string - it reverses a string.
 * @s: the input string.
 * Return: it returns nothing.
 */
void rev_string(char *s)
{
	int count = 0, x, j;
	char *str, temp;

	while (count >= 0)
	{
		if (s[count] == '\0')
			break;
		count++;
	}
	str = s;

	for (x = 0; x < (count - 1); x++)
	{
		for (j = x + 1; j > 0; j--)
		{
			temp = *(str + j);
			*(str + j) = *(str + (j - 1));
			*(str + (j - 1)) = temp;
		}
	}
}
