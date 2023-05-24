#include "shell.h"

/**
* insert_node - Inserts a node at the start of the list(***Done)
* @head: Pointer address to head node
* @str: Field of node str
* @num: index node used by history
*
* Return: size of list
*/
list_t *insert_node(list_t **head, const char *str, int num)
{
list_t *new_node;

if (!head)
return (NULL);

new_node = malloc(sizeof(list_t));
if (!new_node)
return (NULL);

_my_memset((void *)new_node, 0, sizeof(list_t));
new_node->num = num;

if (str)
{
new_node->str = betty_strdup(str);
if (!new_node->str)
{
free(new_node);
return (NULL);
}
}

new_node->next = *head;
*head = new_node;
return (new_node);
}


/**
* addNodeEnd - adds a node to the end of the list(*****Done)
* @head: pointer to pointer to head node
* @str: string field of node
* @num: node index used by history
*
* Return: size of list
*/
list_t *addNodeEnd(list_t **head, const char *str, int num)
{
list_t *newNode, *currentNode;

if (!head)
return (NULL);

currentNode = *head;
newNode = malloc(sizeof(list_t));
if (!newNode)
return (NULL);
_my_memset((void *)newNode, 0, sizeof(list_t));
newNode->num = num;
if (str)
{
newNode->str = betty_strdup(str);
if (!newNode->str)
{
free(newNode);
return (NULL);
}
}
if (currentNode)
{
while (currentNode->next)
currentNode = currentNode->next;
currentNode->next = newNode;
}
else
*head = newNode;
return (newNode);
}

/**
* display_list - displays the string element of a list_t linked list(***Done)
* @list: the pointer to 1st node
*
* Return: the size of list
*/
size_t display_list(const list_t *list)
{
size_t count = 0;

while (list)
{
print_string(list->str ? list->str : "(nil)");
print_string("\n");
list = list->next;
count++;
}

return (count);
}

/**
* delete_node - deletes node at specified index(*****Done)
* @h: address of pointer to the 1st node
* @idx: index of the node to be deleted
*
* Return: 1 on success, 0 on failure
*/
int delete_node(list_t **h, unsigned int idx)
{
list_t *current, *prev;
unsigned int i = 0;

if (!h || !*h)
return (0);

if (!idx)
{
current = *h;
*h = (*h)->next;
free(current->str);
free(current);
return (1);
}

current = *h;
while (current)
{
if (i == idx)
{
prev->next = current->next;
free(current->str);
free(current);
return (1);
}
i++;
prev = current;
current = current->next;
}
return (0);
}
/**
* clear_list - Frees all the nodes of a list(*****Done)
* @head_ptr: Address of pointer to the head node
*
* Return: void
*/
void clear_list(list_t **head_ptr)
{
list_t *current_node, *next_node, *head;

if (!head_ptr || !*head_ptr)
return;

head = *head_ptr;
current_node = head;

while (current_node)
{
next_node = current_node->next;
free(current_node->str);
free(current_node);
current_node = next_node;
}

*head_ptr = NULL;
}

