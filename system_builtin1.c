#include "shell.h"

/**
 * show_alias - you are able to view alias
 * @node: the node connected with alias
 *
 * Return: 0 on success, 1 otherwise
 */
int show_alias(the_list *node)
{
	char *first = NULL;
	char *second = NULL;

	if (node)
	{
		first = locate_char(node->str, '=');
		for (second = node->str; second <= first; second++)
			put_char(*second);
		put_char('\'');
		do_input(first + 1);
		do_input("'\n");
		return (0);
	}
	return (1);
}

/**
 * exit_shell - Helps us leave the shell
 * @dict: user defined structure, which serves a argument
 * Return: an exit which depends on a given exit status
 */
int exit_shell(the_keys *dict)
{
	int check_value;

	if (dict->argv[1])
	{
		check_value = con_err(dict->argv[1]);
		if (check_value == -1)
		{
			dict->state = 2;
			show_error(dict, "The value is not permitted: ");
			print_in(dict->argv[1]);
			print_err('\n');
			return (1);
		}
		dict->control_num = con_err(dict->argv[1]);
		return (-2);
	}
	dict->control_num = -1;
	return (-2);
}

/**
 * get_help - gives information about fuctions
 * @dict: Structure defined by user
 * Return: 0
 */
int get_help(the_keys *dict)
{
	char **arg_array;

	arg_array = dict->argv;
	do_input("Try to implement this function first, then retry\n");
	if (0)
		do_input(*arg_array);
	return (0);
}

/**
 * now_alias - copies the builtin alias
 * @dict: defined structure parameter
 * Return: 0
 */
int now_alias(the_keys *dict)
{
	int i = 0;
	char *p = NULL;
	the_list *node = NULL;

	if (dict->argc == 1)
	{
		node = dict->represent;
		while (node)
		{
			show_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; dict->argv[i]; i++)
	{
		p = locate_char(dict->argv[i], '=');
		if (p)
			put_alias(dict, dict->argv[i]);
		else
			show_alias(pre_node(dict->represent, dict->argv[i], '='));
	}

	return (0);
}
