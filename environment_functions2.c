#include "shell.h"

/**
 * dismiss_env - dismisses or removes current env var
 * @dict: defined struct with pseudo argument
 * @var: the string env var property
 * Return: 1 on succes, 0 otherwise
 */
int dismiss_env(the_keys *dict, char *var)
{
	the_list *node = dict->local;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = what_begin(node->str, var);
		if (p && *p == '=')
		{
			dict->switch_var = prec_rem(&(dict->local), i);
			i = 0;
			node = dict->local;
			continue;
		}
		node = node->next;
		i++;
	}
	return (dict->switch_var);
}

/**
 * this_env - shows us the current environment
 * @dict: Structure parameter
 * Return: 0
 */
int this_env(the_keys *dict)
{
	print_linked(dict->local);
	return (0);
}

/**
 * find_env - helps us get a value for the env representation
 * @dict: Stucture defined by shell maker
 * @envar: environment variable name
 *
 * Return: NULL
 */
char *find_env(the_keys *dict, const char *envar)
{
	the_list *node = dict->local;
	char *a;

	while (node)
	{
		a = what_begin(node->str, envar);
		if (a && *a)
			return (a);
		node = node->next;
	}
	return (NULL);
}

/**
 * unset_myenv - unsets or removes env var
 * @dict: Structure containing ars
 * Return: 0
 */
int unset_myenv(the_keys *dict)
{
	int a = 1;

	if (dict->argc == 1)
	{
		print_in("arguments not enough.\n");
		return (1);
	}
	while (a <= dict->argc)
	{
		dismiss_env(dict, dict->argv[a]);
		a++;
	}
	return (0);
}
