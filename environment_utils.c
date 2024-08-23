#include "main.h"

/**
 * _printenv - Prints the environment variables
 *
 * Return: 0 on success, -1 on failure
 */
int _printenv(void)
{
    int i;

    if (environ == NULL)
        return (-1);

    for (i = 0; environ[i] != NULL; i++)
        printf("%s\n", environ[i]);

    return (0);
}

/**
 * _getenv - Retrieves the value of an environment variable
 * @var: the name of the environment variable
 *
 * Return: the value of the environment variable, or NULL if not found
 */
char *_getenv(char *var)
{
    char **env = environ;
    size_t len = strlen(var);

    while (*env != NULL)
    {
        if (strncmp(*env, var, len) == 0 && (*env)[len] == '=')
            return (*env + len + 1);
        env++;
    }
    return (NULL);
}
