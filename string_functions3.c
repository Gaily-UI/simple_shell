#include "shell.h"

/**
 * *mimic_string - makes a copy of str
 * @to: target
 * @from: source
 *
 * Return: pointer to destination
 */
char *mimic_string(char *to, char *from)
{
	int i = 0;

	if (to == from || from == 0)
		return (to);
	while (from[i])
	{
		to[i] = from[i];
		i++;
	}
	to[i] = 0;
	return (to);
}

/**
 * *merge_them - merges two strings
 * @to: target
 * @from: source
 *
 * Return: buffer destination
 */
char *merge_them(char *to, char *from)
{
	char *retun = to;

	while (*to)
		to++;
	while (*from)
		*to++ = *from++;
	*to = *from;
	return (retun);
}

/**
 * comp_strings - compares two strings
 * @string1: first string
 * @string2: second strang
 *
 * Return: -1 if string1 < string2,
 *    1 if string1 > string2, 0 if string1 == string2
 */
int comp_strings(char *string1, char *string2)
{
	while (*string1 && *string2)
	{
		if (*string2 != *string1)
			return (*string1 - *string2);
		string1++;
		string2++;
	}
	if (*string1 == *string2)
		return (0);
	else
		return (*string1 < *string2 ? -1 : 1);
}

/**
 * do_input - displays string input by user
 * @string: target string
 *
 * Return: void
 */
void do_input(char *string)
{
	int i = 0;

	if (!string)
		return;
	while (string[i] != '\0')
	{
		put_char(string[i]);
		i++;
	}
}
