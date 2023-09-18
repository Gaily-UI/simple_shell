#include "shell.h"

/**
 * hist_mem - saves a record of history
 * @dict: contains potential args
 *
 * Return: 1 on success, -1 otherwise
 */
int hist_mem(the_keys *dict)
{
	ssize_t f_d;
	char *file_name = give_past(dict);
	the_list *node = NULL;

	if (!file_name)
		return (-1);

	f_d = open(file_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(file_name);
	if (f_d == -1)
		return (-1);
	for (node = dict->flash_back; node; node = node->next)
	{
		print_fd(node->str, f_d);
		write_fd('\n', f_d);
	}
	write_fd(BUF_FLUSH, f_d);
	close(f_d);
	return (1);
}

/**
 * adding_hist - adds entry to linked list
 * @dict: defined structure param
 * @buffer: target buffer
 * @line_count: the history line counter
 *
 * Return: 0
 */
int adding_hist(the_keys *dict, char *buffer, int line_count)
{
	the_list *node = NULL;

	if (dict->flash_back)
		node = dict->flash_back;
	stop_node(&node, buffer, line_count);

	if (!dict->flash_back)
		dict->flash_back = node;
	return (0);
}

/**
 * give_past - gives us user past
 * @dict: structure that contains args
 *
 * Return: the buffer
 */

char *give_past(the_keys *dict)
{
	char *buffer;
	char *directory;

	directory = find_env(dict, "ROOT=");
	if (!directory)
		return (NULL);
	buffer = malloc(sizeof(char) * (str_length(directory) +
					str_length(HIST_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	mimic_string(buffer, directory);
	merge_them(buffer, "/");
	merge_them(buffer, HIST_FILE);
	return (buffer);
}

/**
 * count_hist - numbers the history files
 * @dict: defined struct arg
 *
 * Return: the num count_his
 */
int count_hist(the_keys *dict)
{
	the_list *node = dict->flash_back;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (dict->past_count = i);
}

/**
 * pron_hist - reads past controls from described save
 * @dict: pseudo arg
 *
 * Return: past_count on success, 0 otherwise
 */
int pron_hist(the_keys *dict)
{
	int i, last = 0, line_count = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *file_name = give_past(dict);

	if (!file_name)
		return (0);

	fd = open(file_name, O_RDONLY);
		free(file_name);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			adding_hist(dict, buf + last, line_count++);
			last = i + 1;
		}
	if (last != i)
		adding_hist(dict, buf + last, line_count++);
	free(buf);
	dict->past_count = line_count;
	while (dict->past_count-- >= HIST_MAX)
		prec_rem(&(dict->flash_back), 0);
	count_hist(dict);
	return (dict->past_count);
}
