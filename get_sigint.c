#include "shell.h"

/**
 * get_sigprmt - it Handle the crtl + c call in prompt
 * @sig: the  Signal handler
 */
void get_sigprmt(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}
