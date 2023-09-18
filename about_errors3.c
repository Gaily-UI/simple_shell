#include "shell.h"

/**
 * print_err - show char in standard error
 * @chr: target character
 *
 * Return: 1 and -1, on succes and error.
 */
int print_err(char chr)
{
	static int i;
	static char buff[WRITE_BUF_SIZE];

	if (chr == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buff, i);
		i = 0;
	}
	if (chr != BUF_FLUSH)
		buff[i++] = chr;
	return (1);
}

/**
 * print_in - prints out an input by user
 *             in the form of string
 * @string: target string
 *
 * Return: NULL
 */
void print_in(char *string)
{
	int i = 0;

	if (!string)
		return;
	while (string[i] != '\0')
	{
		print_err(string[i]);
		i++;
	}
}

/**
 * print_fd - function prints input string
 * @string: target string
 * @fid: target filedescriptor
 *
 * Return: character number
 */
int print_fd(char *string, int fid)
{
	int a = 0;

	if (!string)
		return (0);
	while (*string)
	{
		a += write_fd(*string++, fid);
	}
	return (a);
}
