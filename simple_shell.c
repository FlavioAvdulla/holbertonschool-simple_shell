#include "main.h"

/**
 * command_read - Reads and processes a command from stdin.
 * @s: The command string to be processed.
 * This function checks if the command is either "exit" or "env".
 * If the command is "exit", the function returns 2 to indicate an exit signal.
 * If the command is "env", the function calls `_printenv` to print the environment variables.
 * Otherwise, it tokenizes the command string and executes the command using `execute`.
 * Return: 0 on successful execution, 1 on failure, 2 if the command is "exit".
 */
int command_read(char *s)
{
	int i;
	char *token = NULL;
	char *cmd_array[100];

	if (strcmp(s, "exit") == 0)
		return (2);
	if (strcmp(s, "env") == 0)
		return (_printenv());
	token = strtok(s, " ");
	i = 0;
	while (token != NULL && i < 100)
	{
		cmd_array[i] = token;
		token = strtok(NULL, " ");
		i++;
	}
	cmd_array[i] = NULL;
	return (execute(cmd_array));
}

/**
 * execute - Executes a command.
 * @cmd_arr: An array of command and its arguments.
 * This function first finds the full path of the command using `command_path`.
 * If the command is found, it forks a new process to execute the command.
 * The parent process waits for the child process to complete and checks the exit status.
 * The child process executes the command using `execvp`.
 * Return: 0 on success, 1 if the command is not found or failed to execute.
 */
int execute(char *cmd_arr[])
{
	pid_t pid;
	char *exe_path;
	int status;

	exe_path = command_path(cmd_arr[0]);
	if (exe_path == NULL)
	{
		fprintf(stderr, "./hsh: 1: %s: not found\n", cmd_arr[0]);
		return (1);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("Error at creating a child process\n");
		exit(1);
	}
	if (pid > 0)
	{
		do {
			waitpid(pid, &status, WUNTRACED);
		}
		while {
		(!WIFEXITED(status) && !WIFSIGNALED(status));
		}
		if (WEXITSTATUS(status) != 0)
		{
			exit(2);
		}
	}
	else if (pid == 0)
	{
		if (execvp(exe_path, cmd_arr) == -1)
		{
			fprintf(stderr, "./hsh: 1: %s: not found\n", cmd_arr[0]);
			exit(127);
		}
	}
	free(exe_path);
	return (0);
}

/**
 * main - Entry point of the shell program.
 * This function continuously prompts the user for input, reads the input command,
 * processes it using `command_read`, and handles the execution of the command.
 * The loop continues until the user inputs "exit" or an error occurs.
 * Return: Always returns 0.
 */
int main(void)
{
	char *line = NULL;
	size_t buf_size = 0;
	ssize_t characters = 0;

	while (1)
	{
		if (isatty(STDIN_FILENO) == 1)
			write(1, "$ ", 2);
		characters = getline(&line, &buf_size, stdin);
		if (characters == -1)
		{
			if (isatty(STDIN_FILENO) == 1)
				write(1, "\n", 1);
			break;
		}
		if (line[characters - 1] == '\n')
			line[characters - 1] = '\0';
		trim_whitespace(line);
		if (*line == '\0')
			continue;
		if (command_read(line) == 2)
			break;
	}
	free(line);
	return (0);
}
