#include "shell.h"

/**
 * main - Runs our shell
 * @ac: Number of inputed arguments
 * @av: Pointer to array of passed arguments
 * @env: Pointer to array of enviromental variables
 * Return: Always 0
 */
int main(int ac, char **av, char **env)
{
	char *buffer = NULL, **command = NULL;
	size_t buf_size = 0;
	ssize_t chars_readed = 0;
	int cicles = 0;
	(void)ac;

	while (1)
	{
		cicles++;
		prompt();
		signal(SIGINT, handle);
		chars_readed = getline(&buffer, &buf_size, stdin);
		if (chars_readed == EOF)
			_EOF(buffer);
		else if (*buffer == '\n')
			free(buffer);
		else
		{
			buffer[_strlen(buffer) - 1] = '\0';
			command = tokening(buffer, " \0");
			free(buffer);
			if (_strcmp(command[0], "exit") != 0)
				shell_exit(command);
			else if (_strcmp(command[0], "cd") != 0)
				change_dir(command[1]);
			else
				create_child(command, av[0], env, cicles);
		}
		fflush(stdin);
		buffer = NULL, buf_size = 0;
	}
	if (chars_readed == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}


/**
 * prompt - Displays the prompt
 * Return: void
 */
void prompt(void)
{
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "MikeNish>> ", 13);
}


/**
 * handle - Handles Ctr + C signal
 * @signals: Signal to handle
 * Return: void
 */
void handle(int signals)
{
	(void)signals;
	write(STDOUT_FILENO, "\nMikeNish>> ", 14);
}


/**
 * _EOF - Checks if buffer is EOF
 * @buffer: Pointer to the input string.
 * Return: void
 */
void _EOF(char *buffer)
{
	if (buffer)
	{
		free(buffer);
		buffer = NULL;
	}

	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "\n", 1);
	free(buffer);
	exit(EXIT_SUCCESS);
}


/**
 * shell_exit - Terminates shell session
 * @command: Pointer to tokenized command
 * Return: void
 */
void shell_exit(char **command)
{
	int sta_tus = 0;

	if (command[1] == NULL)
	{
		free_dp(command);
		exit(EXIT_SUCCESS);
	}

	sta_tus = _atoi(command[1]);
	free_dp(command);
	exit(sta_tus);
}
