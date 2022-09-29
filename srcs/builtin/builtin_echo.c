#include "../../includes/minishell.h"

void	builtin_echo(t_cmd_node *node)
{
	int			option;

	option = FALSE;
	node = node->next;
	if (node == NULL)
	{
		printf("\n");
		g_state.exit_status = 0;
		return ;
	}
	if (node->type == OPTION)
	{
		option = TRUE;
		node = node->next;
	}
	g_state.exit_status = 0;
	if (node == NULL)
		return ;
	while (node->next != NULL)
	{
		printf("%s ", node->cmd);
		node = node->next;
	}
	printf("%s", node->cmd);
	if (option == FALSE)
		printf("\n");
}