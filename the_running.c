#include "shell.h"

/**
 * show_sys - looks for a system command
 * @dict: defined struct parameter
 *
 * Return: -1 in failure, 0 in execution success,
 *   1 if builtin found but not successful,
 *   2 in case if exit
 */
int show_sys(the_keys *dict)
{
	int i, builtin_ret = -1;
	My_table builtin_tbl[] = {
		{"exit", exit_shell},
		{"env", this_env},
		{"help", get_help},
		{"history", show_his},
		{"setenv", set_myenv},
		{"unsetenv", unset_myenv},
		{"cd", change_dir},
		{"alias", now_alias},
		{NULL, NULL}
	};

	for (i = 0; builtin_tbl[i].type; i++)
		if (comp_strings(dict->argv[0], builtin_tbl[i].type) == 0)
		{
			dict->numberer++;
			builtin_ret = builtin_tbl[i].func(dict);
			break;
		}
	return (builtin_ret);
}

/**
 * hsh - this is the loop that defines our shell
 * @dict: defined struct parameter
 * @avector: the main argument vector
 *
 * Return: 0 , 1 on error.
 */
int hsh(the_keys *dict, char **avector)
{
	ssize_t r = 0;
	int inside = 0;

	while (r != -1 && inside != -2)
	{
		remove_struct(dict);
		if (commun(dict))
			do_input("$ ");
		print_err(BUF_FLUSH);
		r = input(dict);
		if (r != -1)
		{
			get_struct(dict, avector);
			inside = show_sys(dict);
			if (inside == -1)
				give_command(dict);
		} else if (commun(dict))
			put_char('\n');
		lib_struct(dict, 0);
	}
	hist_mem(dict);
	lib_struct(dict, 1);
	if (!commun(dict) && dict->state)
		exit(dict->state);
	if (inside == -2)
	{
		if (dict->control_num == -1)
			exit(dict->state);
		exit(dict->control_num);
	}
	return (inside);
}

/**
 * create_command - makes an execution to take place
 * @dict: the defined struct containing parameter
 *
 * Return: void
 */
void create_command(the_keys *dict)
{
	pid_t baby_pid;

	baby_pid = fork();
	if (baby_pid == -1)
	{
		perror("You got an ERROR!:");
		return;
	}
	if (baby_pid == 0)
	{
		if (execve(dict->path, dict->argv, give_env(dict)) == -1)
		{
			lib_struct(dict, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(dict->state));
		if (WIFEXITED(dict->state))
		{
			dict->state = WEXITSTATUS(dict->state);
			if (dict->state == 126)
				show_error(dict, "Permission denied\n");
		}
	}
}

/**
 * give_command - looks for cmd in mem
 * @dict: defined struct containing param
 *
 * Return: void
 */
void give_command(the_keys *dict)
{
	char *path = NULL;
	int a, k;

	dict->path = dict->argv[0];
	if (dict->signal_count == 1)
	{
		dict->numberer++;
		dict->signal_count = 0;
	}
	for (a = 0, k = 0; dict->arg[a]; a++)
		if (!delim_check(dict->arg[a], " \t\n"))
			k++;
	if (!k)
		return;

	path = look_path(dict, find_env(dict, "PATH="), dict->argv[0]);
	if (path)
	{
		dict->path = path;
		create_command(dict);
	}
	else
	{
		if ((commun(dict) || find_env(dict, "This PAth")
					|| dict->argv[0][0] == '/') && detem_exec(dict, dict->argv[0]))
			create_command(dict);
		else if (*(dict->arg) != '\n')
		{
			dict->state = 127;
			show_error(dict, "not found\n");
		}
	}
}
