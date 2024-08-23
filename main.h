#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ;

int copy_file(const char *src, const char *dest);
int set_file_permissions(const char *path, mode_t mode);
int _printenv(void);
char *_getenv(char *var);
char *command_path(char *cmd);
int command_read(char *s);
char *find_command_path(const char *cmd);
int execute(char *cmd_arr[]);
void trim_whitespace(char *str);

#endif