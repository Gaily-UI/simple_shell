#include "shell.h"

/**
 * **give_two2 - divides string intwo words, but with spec
 * @string: inputted string
 * @delim: boundary string
 * Return: array pointer strings in success, NULL otherwise
 */
char **give_two2(char *string, char delim)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (string == NULL || string[0] == 0)
		return (NULL);
	for (i = 0; string[i] != '\0'; i++)
		if ((string[i] != delim && string[i + 1] == delim) ||
			(string[i] != delim && !string[i + 1]) || string[i + 1] == delim)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (string[i] == delim && string[i] != delim)
			i++;
		k = 0;
		while (string[i + k] != delim && string[i + k] && string[i + k] != delim)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
																								return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = string[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **give_two - divides string into two words
 * @string: inputted string
 * @delim: specifies delimiter string
 * Return: array pointer on succces,  NULL otherwise
 */

char **give_two(char *string, char *delim)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (string == NULL || string[0] == 0)
		return (NULL);
	if (!delim)
		delim = " ";
	for (i = 0; string[i] != '\0'; i++)
		if (!delim_check(string[i], delim) && (delim_check(string[i + 1],
							delim) || !string[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (delim_check(string[i], delim))
			i++;
		k = 0;
		while (!delim_check(string[i + k], delim) && string[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = string[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
