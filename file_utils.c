#include "main.h"

/**
 * copy_file - Copies a file from source to destination
 * @src: The source file path
 * @dest: The destination file path
 * Return: 0 on success, -1 on failure
 */
int copy_file(const char *src, const char *dest)
{
    FILE *src_file, *dest_file;
    char buffer[BUFSIZ];
    size_t n;

    src_file = fopen(src, "rb");
    if (src_file == NULL)
    {
        perror("Error opening source file");
        return -1;
    }

    dest_file = fopen(dest, "wb");
    if (dest_file == NULL)
    {
        perror("Error opening destination file");
        fclose(src_file);
        return -1;
    }

    while ((n = fread(buffer, 1, sizeof(buffer), src_file)) > 0)
    {
        if (fwrite(buffer, 1, n, dest_file) != n)
        {
            perror("Error writing to destination file");
            fclose(src_file);
            fclose(dest_file);
            return -1;
        }
    }

    fclose(src_file);
    fclose(dest_file);
    return 0;
}

/**
 * set_file_permissions - Sets the permissions of a file
 * @path: The file path
 * @mode: The permission mode to set
 * Return: 0 on success, -1 on failure
 */
int set_file_permissions(const char *path, mode_t mode)
{
    if (chmod(path, mode) != 0)
    {
        perror("Error setting file permissions");
        return -1;
    }
    return 0;
}
