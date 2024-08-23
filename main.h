#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

extern char **environ;
char *name;

int _strlen(char *string);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
char *_strdup(char *string);
int _strcmp(char *s1, char *s2);
int _str_n_cmp(char *s1, char *s2, int n);

int _printenv(void);
char *_getenv(char *name);

char *command_path(char *cmd);

int command_read(char *s, size_t __attribute__((unused)) characters);
int execute(char *cmd_array[]);
#endif