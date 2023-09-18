#include "shell.h"

/**
 * give_env - gives an array that indicated our environment
 * @dict: defined structure containing pseudo parameter
 * Return: 0
 */
char **give_env(the_keys *dict)
{
	if (!dict->environ || dict->switch_var)
	{
		dict->environ = conv_list(dict->local);
		dict->switch_var = 0;
	}

	return (dict->environ);
}

/**
 * appoint_env - creates a new env var, or modifies existing
 * @dict: Structure containing pseudo args
 * @var: target variable
 * @strval: target string value
 * Return: 0
 */
int appoint_env(the_keys *dict, char *var, char *strval)
{
	char *buffer = NULL;
	the_list *node;
	char *a;

	if (!var || !strval)
		return (0);

	buffer = malloc(str_length(var) + str_length(strval) + 2);
	if (!buffer)
		return (1);
	mimic_string(buffer, var);
	merge_them(buffer, "=");
	merge_them(buffer, strval);
	node = dict->local;
	while (node)
	{
		a = what_begin(node->str, var);
		if (a && *a == '=')
		{
			free(node->str);
			node->str = buffer;
			dict->switch_var = 1;
			return (0);
		}
		node = node->next;
	}
	stop_node(&(dict->local), buffer, 0);
	free(buffer);
	dict->switch_var = 1;
	return (0);
}

/**
 * set_myenv - creates a new environment
 * @dict: Defined structure containing args
 * Return: 0
 */
int set_myenv(the_keys *dict)
{
	if (dict->argc != 3)
	{
		print_in("Incorrect number of arguements\n");
		return (1);
	}
	if (appoint_env(dict, dict->argv[1], dict->argv[2]))
		return (0);
	return (1);
}

/**
 * pop_env - supplies aur linked list with dictionary vars
 * @dict: defined structure containing args
 * Return: 0
 */
int pop_env(the_keys *dict)
{
	the_list *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		stop_node(&node, environ[i], 0);
	dict->local = node;
	return (0);
}
