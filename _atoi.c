#include "shell.h"

/**
 * check_interactive - checks if shell is in interactive mode
 * @info: pointer to struct info_t
 *
 * Return: 1 if shell is in interactive mode, 0 otherwise
 */
int check_interactive(info_t *info)
{
    return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delimiter - checks if a character is a delimiter
 * @c: the character to check
 * @delim: the delimiter string
 * Return: 1 if true, 0 if false
 */
int is_delimiter(char c, char *delim)
{
    while (*delim)
    {
        if (*delim == c)
            return (1);
        delim++;
    }
    return (0);
}

/**
 * _isalpha_custom - checks for alphabetic character
 * @c: The character to check
 * Return: 1 if c is alphabetic, 0 otherwise
 */
int _isalpha_custom(int c)
{
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

/**
 * _atoi_custom - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */
int _atoi_custom(char *s)
{
    int i, sign = 1, flag = 0;
    unsigned int result = 0;

    for (i = 0; s[i] != '\0' && flag != 2; i++)
    {
        if (s[i] == '-')
        {
            sign *= -1;
        }
        if (s[i] >= '0' && s[i] <= '9')
        {
            flag = 1;
            result *= 10;
            result += (s[i] - '0');
        }
        else if (flag == 1)
        {
            flag = 2;
        }
    }

    if (sign == -1)
    {
        return (-result);
    }
    else
    {
        return (result);
    }
}

