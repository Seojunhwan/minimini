#include "minishell.h"

void	builtin_env()
{
	int	i;

	i = 0;
	while (g_state.envp[i])
		printf("%s\n", g_state.envp[i++]);
}
