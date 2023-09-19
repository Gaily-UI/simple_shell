#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <errno.h>
#include <limits.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>

/* general constants */
#define WRITE_BUF_SIZE 1024
#define READ_BUF_SIZE 1024
#define BUF_FLUSH -1

#define CMD_AND		2
#define CMD_CHAIN	3
#define CMD_NORM	0
#define CMD_OR		1

/* during our conversion processes */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* when using the getline function */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	"talk about shell history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct list_string - singly linked list
 * @num: for the numbers
 * @str: the defined string
 * @next: pointer to next node
 */
typedef struct list_string
{
	int num;
	char *str;
	struct list_string *next;
} the_list;

/**
 * struct program_default - contains aguments for our functions
 *       the arguments are of varoius types
 * @arg: structure argument
 * @argv: structure argument vector
 * @numberer: used to number operation lines
 * @signal_count: used to count instruction signals
 * @given_name: represents inline defined names
 * @local: gives our immediate environment info
 * @flash_back: gives us information on operation history
 * @represent: used to represent other defined elements
 * @environ: a system variable that depends on the environment
 * @switch_var: uses to change environment variable
 * @state: value shows the current state of an element
 * @buffer_cmd: stores info on current command
 * @buffer_cmd_type: stores information about the type of cmd
 * @utter_fd: tells us about the fd
 * @past_count: numbers past instruction number
 * @path: directs us to cmd path
 * @argc: numbers the arguments made in a command
 * @control_num: used ti number errors
 */
typedef struct program_default
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int numberer;
	int control_num;
	int signal_count;
	char *given_name;
	the_list *local;
	the_list *flash_back;
	the_list *represent;
	char **environ;
	int switch_var;
	int state;

	char **buffer_cmd;
	int buffer_cmd_type;
	int utter_fd;
	int past_count;
} the_keys;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
			0, 0, 0}

/**
 * struct builtin - contains uiltins that we will use throughout
 * @type: the builtin cmd alerts
 * @func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(the_keys *);
} My_table;

/* parser_functions.c */
int detem_exec(the_keys *, char *);
char *mult_char(char *, int, int);
char *look_path(the_keys *, char *, char *);

/* about_errors1.c */
void show_error(the_keys *, char *);
int show_d(int, int);
void rem_comms(char *);

/* add3numbers.c  */
int add3Nums(int, int, int);

/* about_errors2.c */
int write_fd(char chr, int file_des);
int con_err(char *);
char *change_num(long int, int, int);

/* about_errors3.c */
void print_in(char *);
int print_err(char);
int print_fd(char *string, int fid);

/* checker_and_converter */
int commun(the_keys *);
int delim_check(char, char *);
int check_alpha(int);
int AtoI(char *);

/* environment_functions1 */
int set_myenv(the_keys *);
int pop_env(the_keys *);
char **give_env(the_keys *);
int appoint_env(the_keys *, char *, char *);

/* environment_functions2 */
int dismiss_env(the_keys *, char *);
char *find_env(the_keys *, const char *);
int this_env(the_keys *);
int unset_myenv(the_keys *);

/* functions_for_variables */
int wow_delim(the_keys *, char *, size_t *);
void stat_chain(the_keys *, char *, size_t *, size_t, size_t);
int other_alias(the_keys *);
int other_vars(the_keys *);
int phone_string(char **, char *);

/* string_functions1.c */
char *copyn_string(char *, char *, int);
char *dup_string(const char *);
int put_char(char);

/* string_functions2.c */
char *what_begin(const char *, const char *);
int str_length(char *);
char *concatn_string(char *, char *, int);
char *locate_char(char *, char);

/* string_functions3.c */
char *merge_them(char *, char *);
char *mimic_string(char *, char *);
int comp_strings(char *, char *);
void do_input(char *);

/* linkedlist_functions1.c */
the_list *stop_node(the_list **, const char *, int);
int prec_rem(the_list **, unsigned int);
size_t list_width(const the_list *);
void liberate(the_list **);
size_t all_list(const the_list *);

/* linkedlist_functions2.c */
the_list *beg_node(the_list **, const char *, int);
size_t print_linked(const the_list *);
char **conv_list(the_list *);
the_list *pre_node(the_list *, char *, char);
ssize_t that_node(the_list *, the_list *);

/* memory_functions.c */
int free_ptr(void **);
void *reallocate(void *, unsigned int, unsigned int);
char *same_byte(char *, char, unsigned int);
void do_liberate(char **);

/* prompt_functions.c */
ssize_t input(the_keys *);
int next_line(the_keys *, char **, size_t *);
void block_c(int);
ssize_t pron_buff(the_keys *, char *, size_t *);
ssize_t buff_chain(the_keys *, char **, size_t *);

/* shellhistory_functions.c */
char *give_past(the_keys *dict);
int hist_mem(the_keys *dict);
int pron_hist(the_keys *dict);
int adding_hist(the_keys *dict, char *buffer, int line_count);
int count_hist(the_keys *dict);

/* string_tokenizers.c */
char **give_two(char *, char *);
char **give_two2(char *, char);

/* system_builtin1.c */
int now_alias(the_keys *);
int show_alias(the_list *);
int exit_shell(the_keys *);
int get_help(the_keys *);

/* system_builtin2.c */
int change_dir(the_keys *);
int put_alias(the_keys *, char *);
int show_his(the_keys *);
int rem_alias(the_keys *, char *);

/* the_running.c */
int hsh(the_keys *, char **);
int show_sys(the_keys *);
void give_command(the_keys *);
void create_command(the_keys *);

/* structure_functions.c */
void remove_struct(the_keys *);
void get_struct(the_keys *, char **);
void lib_struct(the_keys *, int);


#endif
