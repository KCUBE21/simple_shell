#include "shell.h"

/**
 * add_sepa_node_end - it adds a separator found at the end
 * of a sepa_list.
 * @head: the head of the linked list.
 * @sepa: the separator found (; | &).
 * Return: it returns address of the head.
 */
sepa_list *add_sepa_node_end(sepa_list **head, char sepa)
{
	sepa_list *new, *temp;

	new = malloc(sizeof(sepa_list));
	if (new == NULL)
		return (NULL);

	new->separator = sepa;
	new->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}

	return (*head);
}

/**
 * free_sepa_list - it frees a sepa_list
 * @head: the head of the linked list.
 * Return: it returns nothing.
 */
void free_sepa_list(sepa_list **head)
{
	sepa_list *temp;
	sepa_list *curr;

	if (head != NULL)
	{
		curr = *head;
		while ((temp = curr) != NULL)
		{
			curr = curr->next;
			free(temp);
		}
		*head = NULL;
	}
}

/**
 * add_line_node_end - it adds a command line at the end
 * of a line_list.
 * @head: the head of the linked list.
 * @line: the command line.
 * Return: the address of the head.
 */
line_list *add_line_node_end(line_list **head, char *line)
{
	line_list *new, *temp;

	new = malloc(sizeof(line_list));
	if (new == NULL)
		return (NULL);

	new->line = line;
	new->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}

	return (*head);
}

/**
 * free_line_list - it frees a line_list
 * @head: the head of the linked list.
 * Return: it  returns nothing.
 */
void free_line_list(line_list **head)
{
	line_list *temp;
	line_list *curr;

	if (head != NULL)
	{
		curr = *head;
		while ((temp = curr) != NULL)
		{
			curr = curr->next;
			free(temp);
		}
		*head = NULL;
	}
}
