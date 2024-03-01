#include "main.h"

/**
 * get_sigint - it Handle the crtl + c call in prompt
 * @sig: the  Signal handler
 */
void get_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}
