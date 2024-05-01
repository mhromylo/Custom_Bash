/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochurko <ochurko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 15:07:34 by mhromylo          #+#    #+#             */
/*   Updated: 2024/04/25 17:02:52 by ochurko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envp	*node_exist(char *name, t_envp *envp_vars)
{
	t_envp	*tmp;

	tmp = envp_vars;
	while (tmp)
	{
		if (str_equal(name, tmp->name_env))
		{
			return (tmp);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

char	*envp_val(char *name, t_envp *env_vars)
{
	t_envp	*temp;

	temp = node_exist(name, env_vars);
	if (!temp)
		return (NULL);
	return (temp->val_env);
}

void	init_list(char *name, char *value, t_envp **list)
{
	t_envp	*new_node;
	t_envp	*tmp_node;

	new_node = malloc(sizeof(t_envp));
	new_node->name_env = ft_strdup(name);
	if (value)
		new_node->val_env = ft_strdup(value);
	new_node->next = NULL;
	if (!*list)
	{
		*list = new_node;
		return ;
	}
	tmp_node = *list;
	while (tmp_node->next)
		tmp_node = tmp_node->next;
	tmp_node->next = new_node;
}

t_envp	*init_envp(char **envp)
{
	t_envp	*list;
	char	*name;
	char	*value;
	int		i;

	list = NULL;
	i = 0;
	while (envp[i])
	{
		name = get_name(envp[i]);
		value = ft_strdup(get_value(envp[i]));
		init_list(name, value, &list);
		free(name);
		free(value);
		i++;
	}
	return (list);
}

void	envp_update(char *name, char *value, t_envp *envp_vars)
{
	t_envp	*tmp;

	tmp = node_exist(name, envp_vars);
	if (!tmp)
	{
		init_list(name, value, &envp_vars);
		return ;
	}
	free(tmp->name_env);
	free(tmp->val_env);
	tmp->name_env = ft_strdup(name);
	tmp->val_env = ft_strdup(value);
}
