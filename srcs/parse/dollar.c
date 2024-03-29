/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junseo <junseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:46:13 by junseo            #+#    #+#             */
/*   Updated: 2022/10/03 05:08:01 by junseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*transform_dollar_token(char *str, int i, char *line)
{
	char		*value;

	if (i == 0 || line[i - 1] != '$')
		return (ft_strdup("$"));
	if (ft_strcmp(str, "\"") == 0)
		return (ft_strdup("$"));
	if (ft_strcmp(str, "?") == 0)
		return (ft_itoa(g_state.exit_status));
	value = get_env_value_via_key(str);
	if (value == NULL)
		return (ft_strdup(""));
	return (ft_strdup(value));
}
