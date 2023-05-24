#include "shell.h"

/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	data_t data[] = { DATA_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				printString(av[0]);
				printString(": 0: Can't open ");
				printString(av[1]);
				eputchar('\n');
				eputchar(FLUSH_BUFFER);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		data->readfd = fd;
	}
	fillEnvList(data);
	read_hist(data);
	shell_loop(data, av);
	return (EXIT_SUCCESS);
}
