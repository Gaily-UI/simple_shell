#include "shell.h"

/**
 * stop_node - appends noode to list
 * @head: address to header node storage location
 * @str: string  field of target node
 * @num: index of the target node
 *
 * Return: list size
 */
the_list *stop_node(the_list **head, const char *str, int num)
{
	the_list *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(the_list));
	if (!new_node)
		return (NULL);
	same_byte((void *)new_node, 0, sizeof(the_list));
	new_node->num = num;
	if (str)
	{
		new_node->str = dup_string(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * prec_rem - deletes a precise node
 * @head: premier node pointer
 * @index: target node index
 *
 * Return: 1 on success, 0 otherwise
 */
int prec_rem(the_list **head, unsigned int index)
{
	the_list *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * liberate - liberates list nodes
 * @head_ptr: points to first node
 *
 * Return: void
 */
void liberate(the_list **head_ptr)
{
	the_list *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}

/**
 * list_width - gives the size of a list
 * @first: first node pointer
 *
 * Return: list width
 */
size_t list_width(const the_list *first)
{
	size_t a = 0;

	while (first)
	{
		first = first->next;
		a++;
	}
	return (a);
}

/**
 * all_list - displays the elements of the linked list
 * @ptr: the header node pointer
 *
 * Return: width of list
 */
size_t all_list(const the_list *ptr)
{
	size_t i = 0;

	while (ptr)
	{
		do_input(change_num(ptr->num, 10, 0));
		put_char(':');
		put_char(' ');
		do_input(ptr->str ? ptr->str : "(nil)");
		do_input("\n");
		ptr = ptr->next;
		i++;
	}
	return (i);
}
