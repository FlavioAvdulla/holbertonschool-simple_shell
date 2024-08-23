#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

int copy_file(const char *src, const char *dest) {
    FILE *source, *destination;
    char ch;

    source = fopen(src, "r");
    if (source == NULL) {
        perror("Error opening source file");
        return 1;
    }

    destination = fopen(dest, "w");
    if (destination == NULL) {
        perror("Error opening destination file");
        fclose(source);
        return 1;
    }

    while ((ch = fgetc(source)) != EOF) {
        fputc(ch, destination);
    }

    fclose(source);
    fclose(destination);
    return 0;
}

int set_file_permissions(const char *path, mode_t mode) {
    if (chmod(path, mode) != 0) {
        perror("Error setting file permissions");
        return 1;
    }
    return 0;
}
