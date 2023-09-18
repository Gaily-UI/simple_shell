#include "shell.h"

/**
 * put_char - writes a chr to our standard output
 * @chr: Target char
 *
 * Return: 1 insuccess , -1 on error.
 */
int put_char(char chr)
{
	static int i;
	static char buffer[WRITE_BUF_SIZE];

	if (chr == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buffer, i);
		i = 0;
	}
	if (chr != BUF_FLUSH)
		buffer[i++] = chr;
	return (1);
}

/**
 * *copyn_string - copies string with n characters
 * @dst_str: target detination
 * @src_str: target source
 * @length: length of chars to be copied
 * Return: cloned string
 */
char *copyn_string(char *dst_str, char *src_str, int length)
{
	int iter1;
	int iter2;
	char *string = dst_str;

	iter1 = 0;
	while (src_str[iter1] != '\0' && iter1 < length - 1)
	{
		dst_str[iter1] = src_str[iter1];
		iter1++;
	}
	if (iter1 < length)
	{
		iter2 = iter1;
		while (iter2 < length)
		{
			dst_str[iter2] = '\0';
			iter2++;
		}
	}
	return (string);
}

/**
 * *dup_string - creates exact copy of string
 * @string: target string
 *
 * Return: pointer to dup string
 */
char *dup_string(const char *string)
{
	int n = 0;
	char *retn;

	if (string == NULL)
		return (NULL);
	while (*string++)
		n++;
	retn = malloc(sizeof(char) * (n + 1));
	if (!retn)
		return (NULL);
	for (n++; n--;)
		retn[n] = *--string;
	return (retn);
}
