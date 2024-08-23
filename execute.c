#include "main.h"

/**
 * execute - Executes the command
 * @cmd_arr: the command line arguments (should be a single command)
 *
 * Return: 0 on success, -1 on failure
 */
int execute(char *cmd_arr[])
{
    int status;
    pid_t child_pid;

    child_pid = fork();

    if (child_pid == 0)
    {
        if (execvp(cmd_arr[0], cmd_arr) == -1)
        {
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    }
    else if (child_pid > 0)
    {
        wait(&status);
    }
    else
    {
        perror("fork");
        return (-1);
    }

    return (0);
}
