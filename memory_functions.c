#include "shell.h"

/**
 * reallocate - allocates a defined mem block
 * @pointr: pointer to prev mem alocated
 * @prev: prev memory size
 * @update: new memory size
 *
 * Return: pointer to new allocation.
 */
void *reallocate(void *pointr, unsigned int prev, unsigned int update)
{
	char *a;

	if (!pointr)
		return (malloc(update));
	if (!update)
		return (free(pointr), NULL);
	if (update == prev)
		return (pointr);

	a = malloc(update);
	if (!a)
		return (NULL);

	prev = prev < update ? prev : update;
	while (prev--)
		a[prev] = ((char *)pointr)[prev];
	free(pointr);
	return (a);
}

/**
 * free_ptr - helps a particular pointer to loose
 * @pointer: pointer address
 *
 * Return: 1 ,  0 in failure.
 */
int free_ptr(void **pointer)
{
	if (pointer && *pointer)
	{
		free(*pointer);
		*pointer = NULL;
		return (1);
	}
	return (0);
}

/**
 * *same_byte - loads memory with identical byte
 * @ptr: poiter to memory location
 * @byte: the filler byte
 * @am: size of allocated memory
 * Return: ptr
 */
char *same_byte(char *ptr, char byte, unsigned int am)
{
	unsigned int i;

	for (i = 0; i < am; i++)
		ptr[i] = byte;
	return (ptr);
}

/**
 * do_liberate - liberate or free a string that contains substrings
 * @strings: substring
 */
void do_liberate(char **strings)
{
	char **str = strings;

	if (!strings)
		return;
	while (*strings)
		free(*strings++);
	free(str);
}
