#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 1024

void display_prompt() {
printf("#cisfun$ ");
}
	int main() {
	char buffer[BUFFER_SIZE];
	char *command;
	pid_t pid;
	int status;

	while (1) {
		display_prompt();

		if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
			printf("\n");
			break;
		}

		buffer[strcspn(buffer, "\n")] = '\0';

		pid = fork();
		if (pid < 0) {
			perror("Fork failed");
			exit(EXIT_FAILURE);
		} else if (pid == 0) {
			command = buffer;
			if (execl(command, command, (char *)NULL) == -1) {
				perror("./shell");
			}
			exit(EXIT_FAILURE);
		} else {
			wait(&status);
		}
	}

	return 0;
}
