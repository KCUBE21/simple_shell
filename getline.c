#include "shell.h"

/**
 * buffer_input - buffers chained commands
 * @info: struct containing parameters
 * @buffer: address of buffer
 * @length: address of length variable
 *
 * Return: number of bytes read
 */
ssize_t buffer_input(info_t *info, char **buffer, size_t *length) {
    ssize_t bytes_read = 0;
    size_t length_pos = 0;

    if (!*length) { /* if buffer is empty, read input */
        free(*buffer);
        *buffer = NULL;
        signal(SIGINT, handle_interrupt);
#if USE_GETLINE
        bytes_read = getline(buffer, &length_pos, stdin);
#else
        bytes_read = custom_getline(info, buffer, &length_pos);
#endif
        if (bytes_read > 0) {
            if ((*buffer)[bytes_read - 1] == '\n') {
                (*buffer)[bytes_read - 1] = '\0'; /* remove trailing newline */
                bytes_read--;
            }
            info->linecount_flag = 1;
            remove_comments(*buffer);
            build_history_list(info, *buffer, info->histcount++);
            /* Check if it's a command chain */
            {
                *length = bytes_read;
                info->cmd_buffer = buffer;
            }
        }
    }
    return bytes_read;
}

/**
 * obtain_input - gets a line without newline
 * @info: parameter struct
 *
 * Return: number of bytes read
 */
ssize_t obtain_input(info_t *info) {
    static char *buffer; /* buffer for command chain */
    static size_t i, j, length;
    ssize_t bytes_read = 0;
    char **buffer_ptr = &(info->arg), *pointer;

    putchar(BUF_FLUSH);
    bytes_read = buffer_input(info, &buffer, &length);
    if (bytes_read == -1) /* EOF */
        return -1;
    if (length) { /* commands left in the chain buffer */
        j = i; /* initialize new iterator to current buffer position */
        pointer = buffer + i; /* get pointer for return */

        check_chain(info, buffer, &j, i, length);
        while (j < length) { /* iterate to semicolon or end */
            if (is_chain(info, buffer, &j))
                break;
            j++;
        }

        i = j + 1; /* increment past nullified ';' */
        if (i >= length) /* reached end of buffer? */
        {
            i = length = 0; /* reset position and length */
            info->cmd_buf_type = CMD_NORMAL;
        }

        *buffer_ptr = pointer; /* pass back pointer to current command position */
        return strlen(pointer); /* return length of current command */
    }

    *buffer_ptr = buffer; /* not a chain, pass back buffer from custom_getline() */
    return bytes_read; /* return length of buffer from custom_getline() */
}

/**
 * read_buffer - reads a buffer
 * @info: parameter struct
 * @buffer: buffer
 * @size: size
 *
 * Return: number of bytes read
 */
ssize_t read_buffer(info_t *info, char *buffer, size_t *size)
{
    ssize_t bytes_read = 0;

    if (*size)
        return 0;
    bytes_read = read(info->readfd, buffer, READ_BUFFER_SIZE);
    if (bytes_read >= 0)
        *size = bytes_read;
    return bytes_read;
}

/**
 * custom_getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: size
 */
int custom_getline(info_t *info, char **ptr, size_t *length)
{
    static char buffer[READ_BUFFER_SIZE];
    static size_t i, length_buffer;
    size_t k;
    ssize_t bytes_read = 0, size = 0;
    char *pointer = NULL, *new_pointer = NULL, *c;

    pointer = *ptr;
    if (pointer && length)
        size = *length;
    if (i == length_buffer)
        i = length_buffer = 0;

    bytes_read = read_buffer(info, buffer, &length_buffer);
    if (bytes_read == -1 || (bytes_read == 0 && length_buffer == 0))
        return -1;

    c = strchr(buffer + i, '\n');
    k = c ? 1 + (unsigned int)(c - buffer) : length_buffer;
    new_pointer = realloc(pointer, size, size ? size + k : k + 1);
    if (!new_pointer) /* Memory allocation failure! */
        return (pointer ? free(pointer), -1 : -1);

    if (size)
        strncat(new_pointer, buffer + i, k - i);
    else
        strncpy(new_pointer, buffer + i, k - i + 1);

    size += k - i;
    i = k;
    pointer = new_pointer;

    if (length)
        *length = size;
    *ptr = pointer;
    return size;
}

/**
 * handle_interrupt - blocks ctrl-C
 * @signal_number: the signal number
 *
 * Return: void
 */
void handle_interrupt(__attribute__((unused)) int signal_number)
{
    puts("\n");
    puts("$ ");
    putchar(BUF_FLUSH);
}

