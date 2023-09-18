#include "shell.h"

/**
 * AtoI - Converts input to integers
 * @str: target input
 * Return: 0 if no numbers in string, converted number otherwise
 */

int AtoI(char *str)
{
	int i;
	int parity = 1;
	int alarm = 0;
	int display;
	unsigned int processed = 0;

	for (i = 0; str[i] != '\0' && alarm != 2; i++)
	{
		if (str[i] == '-')
			parity *= -1;

		if (str[i] >= '0' && str[i] <= '9')
		{
			alarm = 1;
			processed *= 10;
			processed += (str[i] - '0');
		}
		else if (alarm == 1)
			alarm = 2;
	}

	if (parity == -1)
		display = -processed;
	else
		display = processed;

	return (display);
}

/**
 * commun - checks whether shell is interactive
 * @dict: user defined structure
 * Return: 1 or 0 depending on the result.
 */
int commun(the_keys *dict)
{
	return (isatty(STDIN_FILENO) && dict->utter_fd <= 2);
}

/**
 * delim_check - To check if char is a delimiter
 * @c: the character we want to check
 * @delim: the string with delimiter suspision
 * Return: 1 or 0, for true or false.
 */
int delim_check(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * check_alpha - Looks for an alphabetic char
 * @value: the input char
 * Return: 1 if value is alphabetic
 */

int check_alpha(int value)
{
	if ((value >= 'a' && value <= 'z') || (value >= 'A' && value <= 'Z'))
		return (1);
	else
		return (0);
}
