#include "shell.h"

/**
 * get_struct - sets information arguments found in struct
 * @dict: target structure
 * @av: target argument vector
 */
void get_struct(the_keys *dict, char **av)
{
	int i = 0;

	dict->given_name = av[0];
	if (dict->arg)
	{
		dict->argv = give_two(dict->arg, " \t");
		if (!dict->argv)
		{
			dict->argv = malloc(sizeof(char *) * 2);
			if (dict->argv)
			{
				dict->argv[0] = dup_string(dict->arg);
				dict->argv[1] = NULL;
			}
		}
		for (i = 0; dict->argv && dict->argv[i]; i++)
			;
		dict->argc = i;

		other_alias(dict);
		other_vars(dict);
	}
}

/**
 * remove_struct - removes the structure
 * @dict: address
 */
void remove_struct(the_keys *dict)
{
	dict->arg = NULL;
	dict->argv = NULL;
	dict->path = NULL;
	dict->argc = 0;
}

/**
 * lib_struct - liiberates structure
 * @dict: target structure
 * @all: all vars
 * Return: void, its a target function
 */
void lib_struct(the_keys *dict, int all)
{
	do_liberate(dict->argv);
	dict->argv = NULL;
	dict->path = NULL;
	if (all)
	{
		if (!dict->buffer_cmd)
			free(dict->arg);
		if (dict->local)
			liberate(&(dict->local));
		if (dict->flash_back)
			liberate(&(dict->flash_back));
		if (dict->represent)
			liberate(&(dict->represent));
		do_liberate(dict->environ);
		dict->environ = NULL;
		free_ptr((void **)dict->buffer_cmd);
		if (dict->utter_fd > 2)
			close(dict->utter_fd);
		put_char(BUF_FLUSH);
	}
}
