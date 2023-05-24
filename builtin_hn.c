#include "shell.h"

/**
 * shell_exit - Exits shell of the prog
 * @info: Structure containing potential arg. Used to upkeep
 *         const funct prototype.
 * Return: Exits with exit status:
 *         (0) if info->arguments[0] != "exit"
 */
int shell_exit(data_t *info)
{
	int exit_check;

	if (info->arguments[1])  /* If an exit argument */
	{
		exit_check = convertStringToInt(info->arguments[1]);
		if (exit_check == -1)
		{
			info->status = 2;
			displayError(info, "Illegal number: ");
			printString(info->arguments[1]);
			eputchar('\n');
			return (1);
		}
		info->err_num = convertStringToInt(info->arguments[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}


/**
 * dirchange - changes the curr dir of process
 * @info: Struct containing potential arguments. Used to upkeep
 *        const funct prototype.
 * Return: Always 0
 */
int dirchange(data_t *info)
{
	char *currDir, *dir, buffer[1024];
	int chdirRet;

	currDir = getcwd(buffer, 1024);
	if (!currDir)
		print_string("TODO: >>getcwd failure emsg here<<\n");
	if (!info->arguments[1])
	{
		dir = getEnvValue(info, "HOME=");
		if (!dir)
			chdirRet =
				chdir((dir = getEnvValue(info, "PWD=")) ? dir : "/");
		else
			chdirRet = chdir(dir);
	}
	else if (betty_strcmp(info->arguments[1], "-") == 0)
	{
		if (!getEnvValue(info, "OLDPWD="))
		{
			print_string(currDir);
			_write_char('\n');
			return (1);
		}
		print_string(getEnvValue(info, "OLDPWD=")), _write_char('\n');
		chdirRet =
		chdir((dir = getEnvValue(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdirRet = chdir(info->arguments[1]);
	if (chdirRet == -1)
	{
		displayError(info, "can't cd to ");
		printString(info->arguments[1]), eputchar('\n');
	}
	else
	{
		set_env(info, "OLDPWD", getEnvValue(info, "PWD="));
		set_env(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
* cd - Helps change the current dir of the process
* @info: Structure container of potential arguments. Used to maintain
* bash
* Copy code
* constant function prototype.
* Return: Always 0
*/
int cd(data_t *info)
{
char **arg_array;

arg_array = info->arguments;
print_string("help call works. Function not yet implemented \n");
if (0)
print_string(*arg_array);
return (0);
}

