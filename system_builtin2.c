#include "shell.h"

/**
 * put_alias - will put an alias on the string
 * @dict: structure parameter
 * @aliastri: the alias string
 *
 * Return: 0 on success, 1 otherwise
 */
int put_alias(the_keys *dict, char *aliastri)
{
	char *sample;

	sample = locate_char(aliastri, '=');
	if (!sample)
		return (1);
	if (!*++sample)
		return (rem_alias(dict, aliastri));

	rem_alias(dict, aliastri);
	return (stop_node(&(dict->represent), aliastri, 0) == NULL);
}

/**
 * change_dir - Will change your directory
 * @dict: user defined structure, check shell.h
 * Return: 0
 */
int change_dir(the_keys *dict)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		do_input(">>The working directory cannot be fetched, possible error<<\n");
	if (!dict->argv[1])
	{
		dir = find_env(dict, "Root Location");
		if (!dir)
			chdir_ret = chdir((dir = find_env(dict, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (comp_strings(dict->argv[1], "-") == 0)
	{
		if (!find_env(dict, "PREVPWD="))
		{
			do_input(s);
			put_char('\n');
			return (1);
		}
		do_input(find_env(dict, "DonePWD=")), put_char('\n');
		chdir_ret = chdir((dir = find_env(dict, "DonePWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(dict->argv[1]);
	if (chdir_ret == -1)
	{
		show_error(dict, "can't switch to directory ");
		print_in(dict->argv[1]), print_err('\n');
	}
	else
	{
		appoint_env(dict, "prePWD", find_env(dict, "nowPWD="));
		appoint_env(dict, "nowPWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * show_his - shows history info
 * @dict: defined structure containing arguments
 * Return: 0
 */
int show_his(the_keys *dict)
{
	all_list(dict->flash_back);
	return (0);
}

/**
 * rem_alias - removes alias from string
 * @dict: sructutre parameter
 * @aliastri: the string alias
 *
 * Return: 0 on success, 1 otherwise
 */
int rem_alias(the_keys *dict, char *aliastri)
{
	int retval;
	char *a, b;

	a = locate_char(aliastri, '=');
	if (!a)
		return (1);
	b = *a;
	*a = 0;
	retval = prec_rem(&(dict->represent),
	that_node(dict->represent, pre_node(dict->represent, aliastri, -1)));
	*a = b;
	return (retval);
}
