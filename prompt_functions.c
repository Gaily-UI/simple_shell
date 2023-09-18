#include "shell.h"

/**
 * input - requests user input
 * @dict: defined struct
 *
 * Return: the amount of bytes read
 */
ssize_t input(the_keys *dict)
{
	static char *buffer;
	static size_t i, j, length;
	ssize_t r = 0;
	char **buf_p = &(dict->arg), *p;

	put_char(BUF_FLUSH);
	r = buff_chain(dict, &buffer, &length);
	if (r == -1)
		return (-1);
	if (length)
	{
		j = i;
		p = buffer + i;

		stat_chain(dict, buffer, &j, i, length);
		while (j < length)
		{
			if (wow_delim(dict, buffer, &j))
				break;
			j++;
		}
		i = j + 1;
		if (i >= length)
		{
			i = length = 0;
			dict->buffer_cmd_type = CMD_NORM;
		}

		*buf_p = p;
		return (str_length(p));
	}
	*buf_p = buffer;
	return (r);
}

/**
 * buff_chain - stores a series of commands
 * @dict: defined struct
 * @buffer: the buffer
 * @length: number of chars
 *
 * Return: the char read
 */
ssize_t buff_chain(the_keys *dict, char **buffer, size_t *length)
{
	ssize_t read = 0;
	size_t len_p = 0;

	if (!*length)
	{
		/*free_ptr((void **)dict->buffer_cmd);*/
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, block_c);
#if USE_GETLINE
		read = getline(buffer, &len_p, stdin);
#else
		read = next_line(dict, buffer, &len_p);
#endif
		if (read > 0)
		{
			if ((*buffer)[read - 1] == '\n')
			{
				(*buffer)[read - 1] = '\0';
				read--;
			}
			dict->signal_count = 1;
			rem_comms(*buffer);
			adding_hist(dict, *buffer, dict->past_count++);
			if (locate_char(*buffer, ';'))
			{
				*length = read;
				dict->buffer_cmd = buffer;
			}
		}
	}
	return (read);
}

/**
 * block_c - will block control+c command
 * @sig_num: the alert number
 *
 * Return: void
 */
void block_c(__attribute__((unused))int sig_num)
{
	do_input("\n");
	do_input("$ ");
	put_char(BUF_FLUSH);
}

/**
 * pron_buff - tells us what the buffer is al about
 * @dict: defined struct containing parameters
 * @buffer: the target beffer
 * @size: the defined sise
 *
 * Return: tell_buffer
 */
ssize_t pron_buff(the_keys *dict, char *buffer, size_t *size)
{
	ssize_t tell_buffer = 0;

	if (*size)
		return (0);
	tell_buffer = read(dict->utter_fd, buffer, READ_BUF_SIZE);
	if (tell_buffer >= 0)
		*size = tell_buffer;
	return (tell_buffer);
}

/**
 * next_line - shows new line for user input
 * @dict: defined struct which contains parameters
 * @ptr: address of pointer to buffer
 * @length: starage capacity of buffer
 *
 * Return: b
 */
int next_line(the_keys *dict, char **ptr, size_t *length)
{
	static char buffer[READ_BUF_SIZE];
	static size_t i, ln;
	size_t k;
	ssize_t a = 0, b = 0;
	char *p = NULL, *brand = NULL, *c;

	p = *ptr;
	if (p && length)
		b = *length;
	if (i == ln)
		i = ln = 0;

	a = pron_buff(dict, buffer, &ln);
	if (a == -1 || (a == 0 && ln == 0))
		return (-1);

	c = locate_char(buffer + i, '\n');
	k = c ? 1 + (unsigned int)(c - buffer) : ln;
	brand = reallocate(p, b, b ? b + k : k + 1);
	if (!brand)
		return (p ? free(p), -1 : -1);

	if (b)
		concatn_string(brand, buffer + i, k - i);
	else
		copyn_string(brand, buffer + i, k - i + 1);

	b += k - i;
	i = k;
	p = brand;

	if (length)
		*length = b;
																						*ptr = p;
																						return (b);
}
