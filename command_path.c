#include "main.h"

char *command_path(char *cmd)
{
    char *path, *path_copy, *full_path, *token;
    struct stat buf;

    if (cmd == NULL || cmd[0] == '\0')
    {
        fprintf(stderr, "Invalid command\n");
        return (NULL);
    }

    if (cmd[0] == '.' || cmd[0] == '/')
    {
        if (stat(cmd, &buf) == 0)
        {
            return (strdup(cmd));
        }
        else
        {
            fprintf(stderr, "Command '%s' not found\n", cmd);
            return (NULL);
        }
    }

    path = _getenv("PATH");
    if (path == NULL || strlen(path) == 0)
    {
        fprintf(stderr, "PATH variable not found or empty\n");
        return (NULL);
    }

    printf("Using PATH: %s\n", path);

    path_copy = strdup(path);
    if (path_copy == NULL)
    {
        fprintf(stderr, "Error copying PATH\n");
        return (NULL);
    }

    token = strtok(path_copy, ":");
    while (token != NULL)
    {
        full_path = malloc(strlen(token) + strlen(cmd) + 2);
        if (full_path == NULL)
        {
            fprintf(stderr, "Error allocating memory for full path\n");
            free(path_copy);
            return (NULL);
        }

        strcpy(full_path, token);
        strcat(full_path, "/");
        strcat(full_path, cmd);

        if (stat(full_path, &buf) == 0)
        {
            free(path_copy);
            return (full_path);
        }
        
        free(full_path);
        token = strtok(NULL, ":");
    }
    
    free(path_copy);
    fprintf(stderr, "Command '%s' not found in PATH\n", cmd);
    return (NULL);
}
