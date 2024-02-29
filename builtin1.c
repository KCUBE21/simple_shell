#include "shell.h"

/**
 *my_history - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 *@info: Structure containing potential arguments.
 * 
 *Return: Always 0
 */
int my_history(info_t *info)
{
print_list(info->history);
return 0;
}

/**
 *unset_alias - unsets an alias.
 *@info: parameter struct
 *@str: the string alias
 * 
 *Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *str)
{
char *p;
int ret;

p = _strchr(str, '=');
if (!p)
return 1;
*p = '\0';
ret = delete_node_at_index(&(info->alias),
get_node_index(info->alias, str));
*p = '=';
return ret;
}

/**
 *set_alias - sets an alias.
 *@info: parameter struct
 *@str: the string alias
 * 
 *Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
char *p;

p = _strchr(str, '=');
if (!p)
    		return 1;
*p = '\0';
unset_alias(info, str);
*p = '=';
return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 *	print_alias - prints an alias string.
 *	@node: the alias node
 * 
 *	Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
char *p;

if (node)
{
p = _strchr(node->str, '=');
if (p)
{
while (*(++p))
_putchar(*p);
_putchar('\n');
return 0;
        }
    }
    return 1;
}

/**
 * my_alias - mimics the alias builtin (man alias).
 * @info: Structure containing potential arguments.
 * 
 * Return: Always 0
 */
int my_alias(info_t *info)
{
    int i;
    char *p;
    list_t *node;

    if (info->argc == 1)
    {
        node = info->alias;
        while (node)
        {
            print_alias(node);
            node = node->next;
        }
        return 0;
    }

    for (i = 1; info->argv[i]; i++)
    {
        p = _strchr(info->argv[i], '=');
        if (p)
            set_alias(info, info->argv[i]);
        else
            print_alias(node_starts_with(info->alias, info->argv[i], '='));
    }

return 0;
}

