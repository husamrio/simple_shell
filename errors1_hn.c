#include "shell.h"

/**
 * convertStringToInt - Changes a strg to an integer.(***Done)
 * @str: tring to be converted.
 *
 * Return: Converted number if successful, -1 on error or
 * if no numbers in string.
 */
int convertStringToInt(char *str)
{
	int i = 0;
	unsigned long int result = 0;

	if (*str == '+')
		str++;
	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			result *= 10;
			result += (str[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
* displayError - prints an error message(***Done)
* @data: the parameter & return data struct
* @errorString: string containing specified error type
* Return: 0 if no numbers in string, converted number otherwise
* -1 on error
*/
void displayError(data_t *data, char *errorString)
{
printString(data->filename);
printString(": ");
printDecimal(data->linecount, STDERR_FILENO);
printString(": ");
printString(data->arguments[0]);
printString(": ");
printString(errorString);
}

/**
 * printDecimal - prints a decimal (integer) number (base 10)(***Done)
 * @num: the input number
 * @fd: the file descriptor to write to
 *
 * Return: number of characters printed
 */
int printDecimal(int num, int fd)
{
	int (*putChar)(char) = _write_char;
	int i, count = 0;
	unsigned int absolute, current;

	if (fd == STDERR_FILENO)
		putChar = eputchar;
	if (num < 0)
	{
		absolute = -num;
		putChar('-');
		count++;
	}
	else
		absolute = num;
	current = absolute;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (absolute / i)
		{
			putChar('0' + current / i);
			count++;
		}
		current %= i;
	}
	putChar('0' + current);
	count++;

	return (count);
}

/**
 * convertNum - Converts a no. to a string rep in the given base(***Done)
 * @num: Number to convert
 * @base: Base to convert to
 * @flags: Flags for the conversion
 *
 * Return: Pointer to the converted string
 */
char *convertNum(long int num, int base, int flags)
{
	static char *digits;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONV_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	digits = flags & CONV_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = digits[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}
/**
 * shorten_string - function replaces 1st occur of '#' with '\0'(***Done)
 * @str: string address to modify in the prog
 *
 * Return: Always 0 all the time;
 */
void shorten_string(char *str)
{
	int i;

	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == '#' && (!i || str[i - 1] == ' '))
		{
			str[i] = '\0';
			break;
		}
	}
}

