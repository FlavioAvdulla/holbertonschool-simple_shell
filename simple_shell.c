#include "main.h"

/**
 * command_read - Reads and processes a command from stdin
 * @s: The command to read
 * Return: 0 on success, 1 on failure, 2 to exit
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

    if (cmd_array[0] == NULL)
        return (0);

    return (execute(cmd_array));
}

#include "main.h"

/**
 * execute - Executes a command with arguments
 * @cmd_arr: Array of command arguments
 * Return: 0 on success, -1 on failure
 */
int execute(char *cmd_arr[])
{
    pid_t pid;
    int status;
    char *exe_path;

    if (cmd_arr == NULL || cmd_arr[0] == NULL)
        return (-1);

    exe_path = command_path(cmd_arr[0]);
    if (exe_path == NULL)
    {
        fprintf(stderr, "Error: Command not found: %s\n", cmd_arr[0]);
        return (-1);
    }

    pid = fork();
    if (pid == -1)
    {
        perror("Error forking process");
        free(exe_path);
        return (-1);
    }
    else if (pid == 0)
    {
        /* Child process */
        if (execvp(exe_path, cmd_arr) == -1)
        {
            perror("Error executing command");
            free(exe_path);
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        /* Parent process */
        if (waitpid(pid, &status, 0) == -1)
        {
            perror("Error waiting for child process");
            free(exe_path);
            return (-1);
        }

        if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
        {
            fprintf(stderr, "Command exited with status %d\n", WEXITSTATUS(status));
            free(exe_path);
            return (-1);
        }
    }

    free(exe_path);
    return (0);
}

/**
 * main - Entry point of the shell program
 * Return: 0 on success, 1 on failure
 */
int main(void)
{
    char *line = NULL;
    size_t buf_size = 0;
    ssize_t characters = 0;

    while (1)
    {
        if (isatty(STDIN_FILENO))
            write(1, "$ ", 2);

        characters = getline(&line, &buf_size, stdin);
        if (characters == -1)
        {
            if (isatty(STDIN_FILENO))
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
