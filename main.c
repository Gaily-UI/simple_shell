#include "shell.h"

/**
 * main - the function entry
 * @a_c: argument counter
 * @a_v: argument vector
 * Return: 0 on success, 1 otherwise
 */
int main(int a_c, char **a_v)
{
	the_keys dict[] = { INFO_INIT };
	int f_d = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (f_d)
		: "r" (f_d));

	if (a_c == 2)
	{
		f_d = open(a_v[1], O_RDONLY);
		if (f_d == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				print_in(a_v[0]);
				print_in(": 0:Sorry, Can't open ");
				print_in(a_v[1]);
				print_err('\n');
				print_err(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		dict->utter_fd = f_d;
	}
	pop_env(dict);
	pron_hist(dict);
	hsh(dict, a_v);
	return (EXIT_SUCCESS);
}
