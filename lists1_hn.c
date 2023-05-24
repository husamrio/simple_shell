#include "shell.h"

/**
* newfunc_name - Calculates the length of a linked list(*****Done)
* @head: Pointer to the 1st node
*
* Return: Size of the linked list
*/
size_t newfunc_name(const list_t *head)
{
size_t count = 0;

while (head)
{
head = head->next;
count++;
}

return (count);
}

/**
* stringsFromList - array of strings is (*****Done)
* returned from the list->str
* @head: first node pointer
*
* Return: strings Array
*/
char **stringsFromList(list_t *head)
{
list_t *current = head;
size_t count = newfunc_name(head), index;
char **strings;
char *string;

if (!head || !count)
return (NULL);
strings = malloc(sizeof(char *) * (count + 1));
if (!strings)
return (NULL);
for (index = 0; current; current = current->next, index++)
{
string = malloc(str_len(current->str) + 1);
if (!string)
{
for (index = 0; index < count; index++)
free(strings[index]);
free(strings);
return (NULL);
}

string = betty_strcpy(string, current->str);
strings[index] = string;
}
strings[index] = NULL;
return (strings);
}


/**
* display_list_elements - Displays all elements (*****Done)
* of a list_t linked list
* @h: pointer to 1st node
*
* Return: size of list
*/
size_t display_list_elements(const list_t *h)
{
size_t i = 0;

while (h)
{
print_string(convertNum(h->num, 10, 0));
_write_char(':');
_write_char(' ');
print_string(h->str ? h->str : "(nil)");
print_string("\n");
h = h->next;
i++;
}

return (i);
}

/**
* findNode - returns the node whose string (*****Done)
* starts with a given prefix
* @head: pointer to the head of the list
* @prefix: string prefix to match
* @nextChar: the next char after the prefix to match
*
* Returns: matching node or NULL if not found
*/
list_t *findNode(list_t *head, char *prefix, char nextChar)
{
char *match = NULL;

while (head)
{
match = _startsWith(head->str, prefix);
if (match && ((nextChar == -1) || (*match == nextChar)))
return (head);
head = head->next;
}
return (NULL);
}

/**
* find_node_index - finds the index of a node(*****Done)
* @h: pointer list head
* @node: pointer node
*
* Return: index of node or -1
*/
ssize_t find_node_index(list_t *h, list_t *node)
{
size_t i = 0;

while (h)
{
if (h == node)
return (i);

h = h->next;
i++;
}

return (-1);
}

