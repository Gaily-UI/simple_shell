#include "shell.h"

/**
 * other_vars - takes the place of vars in a token string
 * @dict: defined structure containing parameter
 *
 * Return: 1 in succes, 0 in failure
 */
int other_vars(the_keys *dict)
{
	int i = 0;
	the_list *node;

	for (i = 0; dict->argv[i]; i++)
	{
		if (dict->argv[i][0] != '$' || !dict->argv[i][1])
			continue;

	if (!comp_strings(dict->argv[i], "$?"))
	{
		phone_string(&(dict->argv[i]),
		dup_string(change_num(dict->state, 10, 0)));
		continue;
	}
	if (!comp_strings(dict->argv[i], "$$"))
	{
		comp_strings((dict->argv[i]),
		dup_string(change_num(getpid(), 10, 0)));
		continue;
	}
	node = pre_node(dict->local, &dict->argv[i][1], '=');
	if (node)
	{
		phone_string(&(dict->argv[i]),
		dup_string(locate_char(node->str, '=') + 1));
		continue;
	}
	phone_string(&dict->argv[i], dup_string(""));
	}
	return (0);
}

/**
 * stat_chain - the position of delimiter chain
 * @dict: defined structure parameter
 * @buffer: the character buffer
 * @posi: position adddress in buffer
 * @initial: beginning position in buffer
 * @length: width of buffer
 *
 * Return: Void
 */
void stat_chain(the_keys *dict, char *buffer, size_t *posi,
		size_t initial, size_t length)
{
	size_t j = *posi;

	if (dict->buffer_cmd_type == CMD_AND)
	{
		if (dict->state)
		{
			buffer[initial] = 0;
			j = length;
		}
	}
	if (dict->buffer_cmd_type == CMD_OR)
	{
		if (!dict->state)
		{
			buffer[initial] = 0;
			j = length;
		}
	}

	*posi = j;
}

/**
 * wow_delim - checks for the presence of a chain delimiter
 * @dict: defined structure parameter
 * @buffer: defines character buffer
 * @posi: storage position of buffer
 *
 * Return: 1 if located, 0 otherwise
 */
int wow_delim(the_keys *dict, char *buffer, size_t *posi)
{
	size_t j = *posi;

	if (buffer[j] == '|' && buffer[j + 1] == '|')
	{
		buffer[j] = 0;
		j++;
		dict->buffer_cmd_type = CMD_OR;
	}
	else if (buffer[j] == '&' && buffer[j + 1] == '&')
	{
		buffer[j] = 0;
		j++;
		dict->buffer_cmd_type = 2;
	}
	else if (buffer[j] == ';')
	{
		buffer[j] = 0;
		dict->buffer_cmd_type = CMD_CHAIN;
	}
	else
		return (0);
	*posi = j;
	return (1);
}

/**
 * phone_string - will replace string
 * @prev: old string location
 * @update: latest string
 *
 * Return: 1 in succes, 0 in failure
 */
int phone_string(char **prev, char *update)
{
	free(*prev);
	*prev = update;
	return (1);
}

/**
 * other_alias - takes the place of alias in string
 * @dict: defined struct that contains pseudo parameter
 *
 * Return: 1 in succes, 0 in failure
 */
int other_alias(the_keys *dict)
{
	int i;
	the_list *node;
	char *a;

	for (i = 0; i < 10; i++)
	{
		node = pre_node(dict->represent, dict->argv[0], '=');
		if (!node)
			return (0);
		free(dict->argv[0]);
		a = locate_char(node->str, '=');
		if (!a)
			return (0);
		a = dup_string(a + 1);
		if (!a)
			return (0);
		dict->argv[0] = a;
	}
	return (1);
}
