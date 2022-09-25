#include "minishell.h"

void	remove_temp_file(void)
{
	struct stat	s;

	if (stat("heredoc_file", &s) == 0)
		unlink("heredoc_file");
}

void	move_heredoc_curser(int fd)
{
	close(fd);
	ft_putstr_fd("\x1b[1A", 1);
	ft_putstr_fd("\033[2C", 1);
	exit(0);
}

char	*replace_dollar(char *str, int idx, char *line)
{
	char	**split;
	char	*ret;
	char	*name;
	int		envp_idx;

	// if (idx < 1 || line[idx - 1] != '$')
	// 	return (ft_strdup("$"));
	if (ft_strcmp(str, "\"") == 0)      //만약 " 이면 그냥 $반환???? 이거 잘모르겠다.
		return (ft_strdup("$"));
	if (ft_strcmp(str, "?") == 0)
		return (ft_itoa(g_state.exit_status));
	envp_idx = is_in_envp(str);
	if (envp_idx == -1)
		return (ft_strdup(""));
	split = ft_split(g_state.envp[envp_idx], '=');
	if (split == 0)
		return (0);
	ret = ft_strdup(split[1]);
	free_split(split);
	return (ret);
}