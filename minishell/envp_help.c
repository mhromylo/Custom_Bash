/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_help.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhromylo <mhromylo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 16:38:18 by mhromylo          #+#    #+#             */
/*   Updated: 2024/04/26 13:31:12 by mhromylo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_value(char *key_pair)
{
	int	i;

	i = 0;
	while (key_pair[i] != '=' && key_pair[i])
		i++;
	if (!key_pair[i])
		return (NULL);
	return (&key_pair[i + 1]);
}

char	*get_name(char *key_pair)
{
	int	i;

	i = 0;
	while (key_pair[i] != '=' && key_pair[i])
		i++;
	if (i != 0 && key_pair[i - 1] == '+')
		i--;
	return (ft_substr(key_pair, 0, i));
}

void	free_t_envp(t_envp **envp_vars)
{
	t_envp	*tmp;
	t_envp	*next;

	tmp = *envp_vars;
	while (tmp)
	{
		free(tmp->name_env);
		free(tmp->val_env);
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	envp_vars = NULL;
}
