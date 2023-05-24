#include "shell.h"

/**
* shell_loop - main shell loop of program(*****Done)
* @info: the parameter & return info of the struct
* @argumentss: the argumentsument vector from main() program
*
* Return: 0 on success, 1 on error.
*/
int shell_loop(data_t *info, char **argumentss)
{
ssize_t read = 0;
int builtin_return = 0;

while (read != -1 && builtin_return != -2)
{
resetData(info);
if (is_running_interactively(info))
print_string("♔ ♔ ♔ ");
eputchar(FLUSH_BUFFER);
read = getLineInput(info);
if (read != -1)
{
init_data(info, argumentss);
builtin_return = findBuiltinCommand(info);
if (builtin_return == -1)
findCommandInPath(info);
}
else if (is_running_interactively(info))
_write_char('\n');
freeData(info, 0);
}
write_hist(info);
freeData(info, 1);
if (!is_running_interactively(info) && info->status)
exit(info->status);
if (builtin_return == -2)
{
if (info->err_num == -1)
exit(info->status);
exit(info->err_num);
}
return (builtin_return);
}


/**
* findBuiltinCommand - finds a builtin command of program
* @info: the parameter also the return info struct
*
* Return: -1 if builtin command not found,
*         0 if builtin command executed successfully,
*         1 if builtin command found but not successful,
*         -2 if builtin command signals exit()
*/
int findBuiltinCommand(data_t *info)
{
int i, builtinRet = -1;
builtin_table builtintbl[] = {
{"exit", shell_exit},
{"env", printEnv},
{"help", cd},
{"history", display_hist},
{"setenv", set_environ},
{"unsetenv", removeEnvVar},
{"cd", dirchange},
{"alias", myAlias},
{NULL, NULL}
};

for (i = 0; builtintbl[i].type; i++)
{
if (betty_strcmp(info->arguments[0], builtintbl[i].type) == 0)
{
info->lineCount++;
builtinRet = builtintbl[i].func(info);
break;
}
}

return (builtinRet);
}

/**
* findCommandInPath - finds a command in the PATH environment variable
* @info: the parameter & also return info struct
*
* Return: void
*/
void findCommandInPath(data_t *info)
{
char *path = NULL;
int i, count;

info->path = info->arguments[0];
if (info->line_count_flag == 1)
{
info->lineCount++;
info->line_count_flag = 0;
}

for (i = 0, count = 0; info->arg[i]; i++)
{
if (!isChDel(info->arg[i], " \t\n"))
count++;
}

if (!count)
return;

path = findExecutablePath(info, getEnvValue(info, "PATH="), info->arguments[0]);
if (path)
{
info->path = path;
executeCommand(info);
}
else
{
if ((is_running_interactively(info) || getEnvValue(info, "PATH=") || info->arguments[0][0] == '/')
&& isExecutableCommand(info, info->arguments[0]))
{
executeCommand(info);
}
else if (*(info->arg) != '\n')
{
info->status = 127;
displayError(info, "not found\n");
}
}
}


/**
* executeCommand - forks a child process to execute the command
* @info: the parameter & return info struct
*
* Return: void
*/
void executeCommand(data_t *info)
{
pid_t child_pid;

child_pid = fork();
if (child_pid == -1)
{
perror("Error:");
return;
}
if (child_pid == 0)
{
if (execve(info->path, info->arguments, envToStringArray(info)) == -1)
{
freeData(info, 1);
if (errno == EACCES)
exit(126);
exit(1);
}
perror("Error:");
}
else
{
wait(&(info->status));
if (WIFEXITED(info->status))
{
info->status = WEXITSTATUS(info->status);
if (info->status == 126)
displayError(info, "Permission denied\n");
}
}
}

