#include "main.h"

/**
 * execute - Executes a command
 * @cmd_arr: Array of command and arguments
 * Return: 0 on success, -1 on failure
 */
int execute(char *cmd_arr[])
{
    pid_t pid;
    int status;
    char *path;

    if (cmd_arr == NULL || cmd_arr[0] == NULL)
    {
        fprintf(stderr, "Error: Command not provided\n");
        return (-1);
    }

    path = command_path(cmd_arr[0]);
    if (path == NULL)
    {
        fprintf(stderr, "./hsh: 1: %s: not found\n", cmd_arr[0]);
        return (-1);
    }

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        free(path);
        return (-1);
    }
    else if (pid == 0)
    {
        if (execve(path, cmd_arr, environ) == -1)
        {
            perror("execve");
            free(path);
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        waitpid(pid, &status, 0);
        free(path);
        if (WIFEXITED(status))
        {
            return (WEXITSTATUS(status));
        }
        else if (WIFSIGNALED(status))
        {
            fprintf(stderr, "Child process terminated by signal %d\n", WTERMSIG(status));
            return (-1);
        }
        else
        {
            return (-1);
        }
    }
    return (0);
}

/**
 * command_tok - Tokenizes the command input
 * @input: The input string to tokenize
 */
void command_tok(char *input)
{
    char *token;
    char *cmd_arr[1024];
    int i = 0;

    token = strtok(input, " \t\n");
    while (token != NULL)
    {
        cmd_arr[i++] = token;
        token = strtok(NULL, " \t\n");
    }
    cmd_arr[i] = NULL;

    if (execute(cmd_arr) == -1)
    {
        fprintf(stderr, "Execution failed\n");
    }
}

/**
 * main - Entry point of the program
 * Return: 0 on normal exit, EXIT_FAILURE on error
 */
int main(void)
{
    int chars_read, istty;
    char *buff = NULL;
    size_t size = 0;

    while (1)
    {
        istty = isatty(STDIN_FILENO);
        if (istty == 1)
            printf("$ ");

        chars_read = getline(&buff, &size, stdin);

        if (chars_read == -1)
        {
            perror("Error reading input");
            if (buff)
                free(buff);
            exit(EXIT_FAILURE);
        }

        if (strcmp(buff, "env\n") == 0)
        {
            _printenv();
            continue;
        }

        if (strcmp(buff, "\n") == 0)
            continue;

        if (strcmp(buff, "exit\n") == 0)
            break;

        trim_whitespace(buff);

        command_tok(buff);

        if (istty != 1)
            break;
    }
    free(buff);
    return (0);
}
