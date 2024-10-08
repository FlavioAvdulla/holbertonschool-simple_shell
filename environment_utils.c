#include "main.h"

/**
 * _printenv - Prints the environment
 * Return: 0 on success, -1 on failure
 */
int _printenv(void)
{
    int i = 0;

    if (environ == NULL)
    {
        fprintf(stderr, "Environment variables not available\n");
        return (-1);
    }

    while (environ[i] != NULL)
    {
        printf("%s\n", environ[i]);
        i++;
    }
    return (0);
}

/**
 * _getenv - Gets the value of an environment variable
 * @var: The environment variable to get
 * Return: The value of the environment variable, or NULL if not found
 */
char *_getenv(char *var)
{
    int i, len_var;

    if (var == NULL)
    {
        fprintf(stderr, "Environment variable name is NULL\n");
        return (NULL);
    }

    len_var = strlen(var);
    for (i = 0; environ[i] != NULL; i++)
    {
        if (strncmp(environ[i], var, len_var) == 0 && environ[i][len_var] == '=')
            return (&environ[i][len_var + 1]);
    }
    return (NULL);
}

/**
 * trim_whitespace - Trims leading and trailing whitespace from a string
 * @str: The string to trim
 */
void trim_whitespace(char *str)
{
    int i, j;
    int len = strlen(str);

    if (str == NULL)
    {
        fprintf(stderr, "String to trim is NULL\n");
        return;
    }

    i = 0;
    while (str[i] == ' ' || str[i] == '\t')
        i++;
    
    if (i > 0)
    {
        j = 0;
        while (str[i] != '\0')
        {
            str[j] = str[i];
            i++;
            j++;
        }
        str[j] = '\0';
    }

    len = strlen(str);
    i = len - 1;
    while (i >= 0 && (str[i] == ' ' || str[i] == '\t'))
    {
        str[i] = '\0';
        i--;
    }
}