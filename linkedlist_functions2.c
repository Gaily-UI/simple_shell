#include "shell.h"

/**
 * beg_node - adds node at end of linked list
 * @head: poiter to head
 * @str: target string field
 * @num: target num
 *
 * Return: list size
 */
the_list *beg_node(the_list **head, const char *str, int num)
{
	the_list *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(the_list));
	if (!new_head)
		return (NULL);
	same_byte((void *)new_head, 0, sizeof(the_list));
	new_head->num = num;
	if (str)
	{
		new_head->str = dup_string(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * print_linked - shows string elements of linked list
 * @first: premier node
 *
 * Return: width of list
 */
size_t print_linked(const the_list *first)
{
	size_t i = 0;

	while (first)
	{
		do_input(first->str ? first->str : "(nothing)");
		do_input("\n");
		first = first->next;
		i++;
	}
	return (i);
}

/**
 * conv_list - converts the list to array of strings
 * @head: the header node pointer
 *
 * Return: array of strings
 */
char **conv_list(the_list *head)
{
	the_list *node = head;
	size_t i = list_width(head), j;
	char **pops;
	char *pop;

	if (!head || !i)
		return (NULL);
	pops = malloc(sizeof(char *) * (i + 1));
	if (!pops)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		pop = malloc(str_length(node->str) + 1);
		if (!pop)
		{
			for (j = 0; j < i; j++)
				free(pops[j]);
			free(pops);
			return (NULL);
		}
		pop = mimic_string(pop, node->str);
		pops[i] = pop;
	}
	pops[i] = NULL;
	return (pops);
}

/**
 * pre_node - returns node base on prefix string
 * @head: header node
 * @begin: the prefix string
 * @c: the char after the prefix string
 *
 * Return: NULL in case if failure, or node that matches
 */
the_list *pre_node(the_list *head, char *begin, char c)
{
	char *p = NULL;

	while (head)
	{
		p = what_begin(head->str, begin);
		if (p && ((c == -1) || (*p == c)))
			return (head);
		head = head->next;
	}
	return (NULL);
}

/**
 * that_node - gets particular node
 * @li_h: header node pointer
 * @ptr: node pointer
 *
 * Return: node index, or -1 in failure
 */
ssize_t that_node(the_list *li_h, the_list *ptr)
{
	size_t i = 0;

	while (li_h)
	{
		if (li_h == ptr)
			return (i);
		li_h = li_h->next;
		i++;
	}
	return (-1);
}
