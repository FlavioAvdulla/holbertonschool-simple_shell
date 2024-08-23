#include "main.h"

/**
 * command_path - Finds the full path of a command
 * @cmd: the command to find
 *
 * Return: full path of the command, or NULL if not found
 */
char *command_path(char *cmd)
{
    char *path_env, *path, *full_path;
    struct stat st;

    path_env = getenv("PATH");
    if (path_env == NULL)
        return (NULL);

    path = strtok(path_env, ":");
    while (path != NULL)
    {
        full_path = malloc(strlen(path) + strlen(cmd) + 2);
        if (full_path == NULL)
            return (NULL);

        sprintf(full_path, "%s/%s", path, cmd);
        if (stat(full_path, &st) == 0 && S_ISREG(st.st_mode) && (st.st_mode & S_IXUSR))
            return (full_path);

        free(full_path);
        path = strtok(NULL, ":");
    }

    return (NULL);
}
