#include "shell.h"

/**
 * show_error - shows us error msg
 * @dict: defined struct parameter
 * @string: string containing specified error type
 * Return: is void as defined
 */
void show_error(the_keys *dict, char *string)
{
	print_in(dict->given_name);
	print_in(": ");
	show_d(dict->numberer, 2);
	print_in(": ");
	print_in(dict->argv[0]);
	print_in(": ");
	print_in(string);
}

/**
 * show_d - shows decimal equivalent of number
 * @a: target
 * @file_des: filedescriptor
 *
 * Return: number of chars printed
 */
int show_d(int a, int file_des)
{
	int (*__putchar)(char) = put_char;
	int i, cnt = 0;
	unsigned int abs, current;

	if (file_des == STDERR_FILENO)
		__putchar = print_err;
	if (a < 0)
	{
		abs = -a;
		__putchar('-');
		cnt++;
	}
	else
		abs = a;
	current = abs;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (abs / i)
		{
			__putchar('0' + current / i);
			cnt++;
		}
		current %= i;
	}
	__putchar('0' + current);
	cnt++;

	return (cnt);
}

/**
 * rem_comms - replaces '#' with '\0'
 * @buffer: stores string to modify
 *
 * Return: 0;
 */
void rem_comms(char *buffer)
{
	int i;

	for (i = 0; buffer[i] != '\0'; i++)
	{
		if (buffer[i] == '#' && (!i || buffer[i - 1] == ' '))
		{
			buffer[i] = '\0';
			break;
		}
	}
}
