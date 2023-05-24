#ifndef _SHELL_H_
#define _SHELL_H_

#include <errno.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define FLUSH_BUFFER -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONV_LOWERCASE	1
#define CONV_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
* struct liststr- A structure representing a singly linked list.
* @num: The numeric field of the node.
* @str: A string associated with the node.
* @next: A pointer to the next node in the list.
*/
typedef struct liststr
{
int num;
char *str;
struct liststr *next;
} list_t;

/**
* struct passinfo -A structure containing pseudo-arguments
* to be passed into a function,
* allowing for a uniform function pointer struct prototype.
* @arg: A string generated from getline that contains arguments.
* @arguments: An array of strings generated from arg.
* @path: A string representing the current command's path.
* @argc: The argument count.
* @err_num: The error code for exit() calls.
* @linecount: If enabled, count this line of input.
* @filename: The filename of the program.
* @env: A linked list serving as a local copy of the environ
* @environ: A custom copy of environ obtained from the linked list env.
* @history: The history node.
* @alias: The alias node.
* @env_changed: A flag indicating if environ has been changed.
* @status: The return status of the last executed command.
* @cmd_buffer: The address of a pointer to cmd_buf, enabled if chaining.
* @commandbuffertype: The type of , which can be CMD_type, ||, &&, or ;.
* @readfd: The file descriptor from which to read line input.
* @line_count_flag: function descibes count flag
* @hist_count:The count of history line numbers.
*/
typedef struct passinfo
{
char *arg;
char **arguments;
char *path;
int argc;
unsigned int linecount;
int err_num;
int line_count_flag;
char *filename;
list_t *env;
list_t *history;
list_t *alias;
char **environ;
int env_changed;
int status;

char **cmd_buffer; /* pointer to cmd ; chain buffer, for memory mangement */
int commandbuffertype; /* CMD_type ||, &&, ; */
int readfd;
int hist_count;
} data_t;

#define DATA_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
0, 0, 0}

/**
* struct builtin - representing a built-in command and its related function.
* @type: The flag indicating the built-in command.
* @func: The function associated with the built-in command.
*/
typedef struct builtin
{
	char *type;
	int (*func)(data_t *);
} builtin_table;

/* shell_loop.c */
int shell_loop(data_t *info, char **argumentss);
int findBuiltinCommand(data_t *info);
void findCommandInPath(data_t *info);
void executeCommand(data_t *info);

/* parser.c */
int isExecutableCommand(data_t *info, char *path);
char *duplicateSubstring(char *str, int start, int stop);
char *findExecutablePath(data_t *info, char *pathString, char *command);

/* errors.c */
void printString(char *str);
int eputchar(char c);
int write_character(char c, int fd);
int _putstr_fd(char *str, int fd);

/* string.c */
int str_len(char *str);
int betty_strcmp(char *str1, char *str2);
char *_startsWith(const char *haystack, const char *needle);
char *betty_str_concat(char *dest, char *src);

/* string1.c */
char *betty_strcpy(char *dest, char *src);
char *betty_strdup(const char *str);
void print_string(char *string);
int _write_char(char c);

/* exits.c */
char *betty_strncpy(char *dest, char *src, int n);
char *string_nconcat(char *dest, char *src, int n);
char *find_character(char *str, char ch);

/* tokenizer.c */
char **split_string(char *str, char *delim);
char **my_split_string(char *str, char delim);

/* realloc.c */
char *_my_memset(char *ptr, char value, unsigned int num);
void free_string_array(char **str_array);
void *realloc_block(void *, unsigned int, unsigned int);

/* memory.c */
int free_ptr(void **ptr);

/* stringToInteger.c */
int is_running_interactively(data_t *info);
int isChDel(char, char *);
int isAlphabetic(int c);
int stringToInteger(char *str);

/* errors1.c */
int convertStringToInt(char *str);
void displayError(data_t *data, char *errorString);
int printDecimal(int num, int fd);
char *convertNum(long int num, int base, int flags);
void shorten_string(char *str);

/* builtin.c */
int shell_exit(data_t *info);
int dirchange(data_t *info);
int cd(data_t *info);

/* builtin1.c */
int display_hist(data_t *info);
int removeAlias(data_t *info, char *alias);
int setAlias(data_t *info, char *aliasStr);
int printAlias(list_t *listNode);
int myAlias(data_t *info);

/*getline.c */
ssize_t getLineInput(data_t *data);
int get_next_line(data_t *, char **, size_t *);
void blockSigint(int);

/* getinfo.c */
void resetData(data_t *);
void init_data(data_t *, char **);
void freeData(data_t *, int);

/* environ.c */
int printEnv(data_t *data);
char *getEnvValue(data_t *, const char *);
int set_environ(data_t *);
int removeEnvVar(data_t *);
int fillEnvList(data_t *);

/* getenv.c */
char **envToStringArray(data_t *);
int EnvVaremove(data_t *, char *);
int set_env(data_t *, char *, char *);


/* history.c */
char *getHistFile(data_t *);
int write_hist(data_t *data);
int read_hist(data_t *d);
int add_hist_entry(data_t *d, char *buffer, int count);
int update_history(data_t *data);

/* lists.c */
list_t *insert_node(list_t **head, const char *str, int num);
list_t *addNodeEnd(list_t **head, const char *str, int num);
size_t display_list(const list_t *list);
int delete_node(list_t **h, unsigned int idx);
void clear_list(list_t **head_ptr);

/* lists1.c */
size_t newfunc_name(const list_t *head);
char **stringsFromList(list_t *head);
size_t display_list_elements(const list_t *h);
list_t *findNode(list_t *head, char *prefix, char nextChar);
ssize_t find_node_index(list_t *h, list_t *node);

/* vars.c */
int isChain(data_t *, char *, size_t *);
void contChain(data_t *, char *, size_t *, size_t, size_t);
int replaceAlias(data_t *);
int replaceVars(data_t *);
int updateString(char **, char *);

#endif
