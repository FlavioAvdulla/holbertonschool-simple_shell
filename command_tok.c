#include "main.h"

/**
 * command_tok - Tokenizes the command line (limited to one-word commands)
 * @line: the command line
 *
 * Return: 0 on success, -1 on failure
 */
int command_tok(char *line)
{
    char *exec_args[2];
    exec_args[0] = line;
    exec_args[1] = NULL;

    if (access(line, X_OK) != 0 && command_path(line) == NULL)
    {
        fprintf(stderr, "Command not found: %s\n", line);
        return (-1);
    }

    return (execute(exec_args));
}
