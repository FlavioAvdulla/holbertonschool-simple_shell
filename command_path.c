#include "main.h"

/**
 * command_path - Finds the full path of a command
 * @cmd: The command to find
 * Return: The full path of the command or NULL if not found
 */
char *command_path(char *cmd)
{
    char *path, *path_copy, *full_path, *token;
    struct stat buf;

    path = _getenv("PATH");
    if (path == NULL)
    {
        fprintf(stderr, "Error: PATH environment variable not found\n");
        return (NULL);
    }
    
    path_copy = strdup(path);
    if (path_copy == NULL)
    {
        perror("Error duplicating PATH");
        return (NULL);
    }
    
    token = strtok(path_copy, ":");
    while (token != NULL)
    {
        full_path = malloc(strlen(token) + strlen(cmd) + 2);
        if (full_path == NULL)
        {
            perror("Error allocating memory for full path");
            free(path_copy);
            return (NULL);
        }
        strcpy(full_path, token);
        strcat(full_path, "/");
        strcat(full_path, cmd);
        if (stat(full_path, &buf) == 0 && S_ISREG(buf.st_mode) && (buf.st_mode & S_IXUSR))
        {
            free(path_copy);
            return (full_path);
        }
        free(full_path);
        token = strtok(NULL, ":");
    }
    free(path_copy);
    
    if (stat(cmd, &buf) == 0 && S_ISREG(buf.st_mode) && (buf.st_mode & S_IXUSR))
        return (strdup(cmd));
    
    fprintf(stderr, "Error: Command not found: %s\n", cmd);
    return (NULL);
}
