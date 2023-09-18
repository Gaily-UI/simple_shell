#include "shell.h"

/**
 * write_fd - writes char to precise file descriptor
 * @chr: The target char
 * @file_des: The filedescriptor
 *
 * Return: 1 if in success and -1 in error.
 */
int write_fd(char chr, int file_des)
{
	static int i;
	static char buffer[WRITE_BUF_SIZE];

	if (chr == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(file_des, buffer, i);
		i = 0;
	}
	if (chr != BUF_FLUSH)
	buffer[i++] = chr;
	return (1);
}

/**
 * change_num - converts input to integers
 * @digit: the number
 * @base_val: the base of the number
 * @alarm: alerts
 *
 * Return: string
 */
char *change_num(long int digit, int base_val, int alarm)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = digit;

	if (!(alarm & CONVERT_UNSIGNED) && digit < 0)
	{
		n = -digit;
		sign = '-';
	}
	array = alarm & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do {
		*--ptr = array[n % base_val];
		n /= base_val;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * con_err - converts an error string to int
 * @string: the target string
 * Return: 0 or -1, depending in success
 */
int con_err(char *string)
{
	int i = 0;
	unsigned long int value = 0;

	if (*string == '+')
		string++;
	for (i = 0;  string[i] != '\0'; i++)
	{
		if (string[i] >= '0' && string[i] <= '9')
		{
			value *= 10;
			value += (string[i] - '0');
			if (value > 2147483647)
				return (-1);
		}
		else
			return (-1);
	}
	return (value);
}
