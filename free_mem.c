#include "shell.h"

/**
 * free_dp - Frees all the memory allocated for command
 * @command: Pointer to allocated memory to free
 * Return: void
 */
void free_dp(char **command)
{
	size_t i = 0;

	if (command == NULL)
		return;

	while (command[i])
	{
		free(command[i]);
		i++;
	}

	if (command[i] == NULL)
		free(command[i]);
	free(command);
}


/**
 * free_exit - Frees all the memory allocated and exit
 * @command: Pointer to allocated command memory to free
 * Return: void
 */
void free_exit(char **command)
{
	size_t i = 0;

	if (command == NULL)
		return;

	while (command[i])
	{
		free(command[i]);
		i++;
	}

	if (command[i] == NULL)
		free(command[i]);
	free(command);
	exit(EXIT_FAILURE);
}
