#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LEN 1024

int main(void)
{
	char command[MAX_COMMAND_LEN];
	char *argv[2];
	pid_t pid;
	int status;

	while (1)
	{
		printf("#cisfun$ ");
		fflush(stdout);

		if (fgets(command, MAX_COMMAND_LEN, stdin) == NULL)
		{
			if (feof(stdin))
			{
				printf("\n");
				break;
			}
			perror("fgets");
			continue;
		}

		command[strcspn(command, "\n")] = 0;

		if (command[0] == '\0')
			continue;

		argv[0] = command;
		argv[1] = NULL;

		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			continue;
		}

		if (pid == 0)
		{
			if (execve(argv[0], argv, environ) == -1)
			{
				perror("./shell");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			wait(&status);
		}
	}

	return 0;
}
