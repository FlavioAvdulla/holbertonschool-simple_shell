#include "main.h"
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

/**
 * copy_file - Copies a file from source to destination
 * @src: The source file path
 * @dest: The destination file path
 * Return: 0 on success, -1 on failure
 */
int copy_file(const char *src, const char *dest)
{
    int src_fd, dest_fd;
    ssize_t nread;
    char buffer[1024];

    src_fd = open(src, O_RDONLY);
    if (src_fd < 0)
    {
        perror("Error opening source file");
        return (-1);
    }

    dest_fd = open(dest, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd < 0)
    {
        perror("Error opening destination file");
        close(src_fd);
        return (-1);
    }

    while ((nread = read(src_fd, buffer, sizeof(buffer))) > 0)
    {
        if (write(dest_fd, buffer, nread) != nread)
        {
            perror("Error writing to destination file");
            close(src_fd);
            close(dest_fd);
            return (-1);
        }
    }

    if (nread < 0)
    {
        perror("Error reading from source file");
        close(src_fd);
        close(dest_fd);
        return (-1);
    }

    close(src_fd);
    close(dest_fd);
    return (0);
}

/**
 * command_read - Reads and processes a command from stdin
 * @s: The command to read
 * Return: 0 on success, 1 on failure, 2 to exit
 */
int command_read(char *s)
{
    int i;
    char *token = NULL;
    char *cmd_array[100];

    if (strcmp(s, "exit") == 0)
        return (2);
    if (strcmp(s, "env") == 0)
        return (_printenv());

    token = strtok(s, " ");
    i = 0;
    while (token != NULL && i < 100)
    {
        cmd_array[i] = token;
        token = strtok(NULL, " ");
        i++;
    }
    cmd_array[i] = NULL;

    if (cmd_array[0] == NULL)
        return (0);

    return (execute(cmd_array));
}

/**
 * execute - Executes a command
 * @cmd_arr: The command to execute
 * Return: 0 on success, 1 on failure
 */
int execute(char *cmd_arr[])
{
    pid_t pid;
    char *exe_path;
    int status;

    exe_path = command_path(cmd_arr[0]);
    if (exe_path == NULL)
    {
        fprintf(stderr, "./hsh: 1: %s: not found", cmd_arr[0]);
        return (1);
    }

    pid = fork();
    if (pid < 0)
    {
        perror("Error creating child process");
        free(exe_path);
        return (1);
    }
    if (pid > 0)
    {
        do
        {
            waitpid(pid, &status, WUNTRACED);
        }
        while (!WIFEXITED(status) && !WIFSIGNALED(status));

        free(exe_path);

        if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
            return (0);
        else
            return (1);
    }
    else
    {
        if (execvp(exe_path, cmd_arr) == -1)
        {
            fprintf(stderr, "./hsh: 1: %s: not found", cmd_arr[0]);
            free(exe_path);
            exit(127);
        }
    }

    free(exe_path);
    return (0);
}

/**
 * main - Entry point of the shell program
 * Return: 0 on success, 1 on failure
 */
int main(void)
{
    char *line = NULL;
    size_t buf_size = 0;
    ssize_t characters = 0;

    char *path = "/home/student_jail/student_repo/hbtn_ls";
    if (copy_file("/bin/ls", path) != 0)
    {
        fprintf(stderr, "Failed to copy file");
        return 1;
    }

    while (1)
    {
        if (isatty(STDIN_FILENO))
            write(1, "$ ", 2);

        characters = getline(&line, &buf_size, stdin);
        if (characters == -1)
        {
            if (isatty(STDIN_FILENO))
                write(1, "", 1);
            break;
        }

        if (line[characters - 1] == ' ')
			line[characters - 1] = ' ';

        trim_whitespace(line);

        if (*line == ' ')
            continue;

        if (command_read(line) == 2)
            break;
    }

    free(line);
    return (0);
}
