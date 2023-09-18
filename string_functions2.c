#include "shell.h"

/**
 * *what_begin - checks our string beginning
 * @search_string: str we want to locate
 * @find_string: part of the main string
 *
 * Return: searchstring address or NULL
 */
char *what_begin(const char *search_string, const char *find_string)
{
	while (*find_string)
		if (*find_string++ != *search_string++)
			return (NULL);
	return ((char *)search_string);
}

/**
 * str_length - gives the width of a string
 * @string: target string
 *
 * Return: string length
 */
int str_length(char *string)
{
	int a = 0;

	if (!string)
		return (0);

	while (*string++)
		a++;
	return (a);
}

/**
 * *concatn_string - joins two strings
 * @to: target
 * @from: origin
 * @n: number of bytes involved
 * Return: joint string
 */
char *concatn_string(char *to, char *from, int n)
{
	int p, q;
	char *s = to;

	p = 0;
	q = 0;
	while (to[p] != '\0')
		p++;
	if (from[q] != '\0' && q < n)
	{
		to[p] = from[q];
		p++;
		q++;
	}
	if (q < n)
		to[p] = '\0';
	return (s);
}

/**
 * *locate_char - helps locate a char
 * @string: target string
 * @chr: target char
 * Return: an indication to memory location
 */
char *locate_char(char *string, char chr)
{
	if (*string++ != '\0')
	{
		if (*string == chr)
		{
			return (string);
		}
	}

	return (NULL);
}
