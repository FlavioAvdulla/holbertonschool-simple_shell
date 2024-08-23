#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ;

int _printenv(void);
char *_getenv(char *var);

char *command_path(char *cmd);

void trim_space(char *s);

int command_tok(char *line);
int execute(char *cmd_arr[]);

void free_args(char *s[]);

#endif
