#include "minishell.h"

void	builtin_pwd()
{
	char	*curr_dir;

	curr_dir = getcwd(NULL, 0);
	if (curr_dir == NULL)
		printf("getcwd() cannot excute in fun_pwd\n");
	else
	{
		printf("%s\n", curr_dir);
		free(curr_dir);
	}
}