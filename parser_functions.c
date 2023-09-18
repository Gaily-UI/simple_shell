#include "shell.h"

/**
 * *look_path - locates command in input
 * @dict: struct containing pseudo args
 * @string: target string
 * @command: target command
 *
 * Return: command path or NULL
 */
char *look_path(the_keys *dict, char *string, char *command)
{
	int i = 0, pos = 0;
	char *path;

	if (!string)
		return (NULL);
	if ((str_length(command) > 2) && what_begin(command, "./"))
	{
		if (detem_exec(dict, command))
			return (command);
	}
	while (1)
	{
		if (!string[i] || string[i] == ':')
		{
			path = mult_char(string, pos, i);
			if (!*path)
				merge_them(path, command);
			else
			{
				merge_them(path, "/");
				merge_them(path, command);
			}
			if (detem_exec(dict, path))
				return (path);
			if (!string[i])
				break;
			pos = i;
		}
		i++;
	}
	return (NULL);
}

/**
 * mult_char - creates char duplicates
 * @str: directory string
 * @begin: beginnin index
 * @end: ending index
 *
 * Return: buffer
 */
char *mult_char(char *str, int begin, int end)
{
	static char buffer[READ_BUF_SIZE];
	int i = 0, j = 0;

	for (j = 0, i = begin; i < end; i++)
		if (str[i] != ':')
			buffer[j++] = str[i];
	buffer[j] = 0;
	return (buffer);
}

/**
 * detem_exec - finds the execution state of a file
 * @dict: defined paramter struct
 * @way: direction or way to file
 *
 * Return: 1 , 0 in failure
 */
int detem_exec(the_keys *dict, char *way)
{
	struct stat td;

	(void)dict;
	if (!way || stat(way, &td))
		return (0);

	if (td.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}
