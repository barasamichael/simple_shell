#include "shell.h"

/**
 * create_child - Creates a sub process
 * @command: Pointer to tokenized command
 * @name: Pointer to the name of shell
 * @env: Pointer to the enviromental variables
 * @cicles: Number of executed cicles
 * Return: void
 */
void create_child(char **command, char *name, char **env, int cicles)
{
	int pid = 0;
	int status = 0;
	int wait_error = 0;

	pid = fork();
	if (pid < 0)
	{
		perror("Error: ");
		free_exit(command);
	}
	else if (pid == 0)
	{
		execute(command, name, env, cicles);
		free_dp(command);
	}
	else
	{
		wait_error = waitpid(pid, &status, 0);
		if (wait_error < 0)
		{
			free_exit(command);
		}
		free_dp(command);
	}
}


/**
  * change_dir - Changes working directory.
  * @path: new current working directory.
  * Return: 0 on success, -1 on failure.
  */
int change_dir(const char *path)
{
	char *buf = NULL;
	size_t size = 1024;

	if (path == NULL)
		path = getcwd(buf, size);
	if (chdir(path) == -1)
	{
		perror(path);
		return (98);
	}
	return (1);
}
