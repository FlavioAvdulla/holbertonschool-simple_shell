#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;  // Add this line to declare environ

#define BUFFER_SIZE 1024

int main(void)
{
	char buffer[BUFFER_SIZE];
	char *args[2];
	pid_t pid;
	int status;

	while (1)
	{
		printf("#cisfun$ ");
		
		if (fgets(buffer, BUFFER_SIZE, stdin) == NULL)
		{
			if (feof(stdin)) {
				printf("\n");
				break;
			}
			perror("fgets");
			continue;
		}

		buffer[strcspn(buffer, "\n")] = '\0';

		if (buffer[0] == '\0')
			continue;

		args[0] = buffer;
		args[1] = NULL;

		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			if (execve(args[0], args, environ) == -1)
			{
				perror("./shell");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			if (wait(&status) == -1)
			{
				perror("wait");
			}
		}
	}

	return 0;
}
