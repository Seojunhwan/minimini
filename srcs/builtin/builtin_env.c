#include "../../includes/minishell.h"

void	builtin_env()
{
	t_env_node	*node;

	node = g_state.env_head;
	while (node)
	{
		printf("%s=%s\n",node->key, node->value);
		node = node->next;
	}
}
