/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochurko <ochurko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:46:32 by mhromylo          #+#    #+#             */
/*   Updated: 2024/04/26 18:17:57 by ochurko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_envp_var(char *name, t_envp **envp_vars)
{
	t_envp	*tmp;
	t_envp	*prev;

	tmp = *envp_vars;
	prev = NULL;
	while (tmp != NULL)
	{
		if (str_equal(tmp->name_env, name))
		{
			if (prev == NULL)
				*envp_vars = tmp->next;
			else
				prev->next = tmp->next;
			free(tmp->name_env);
			free(tmp->val_env);
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

int	is_valid_varname_unset(char *name)
{
	if (!ft_isalpha(*name))
		return (0);
	while (*name)
	{
		if (!is_varname(*name))
			return (0);
		name++;
	}
	return (1);
}

int	unset(char **args, t_envp **envp_vars)
{
	char	*name;
	int		exit_status;

	args++;
	if (!*args)
		return (0);
	while (*args)
	{
		name = *args;
		if (*name == '-')
		{
			ft_putstr_fd("unset: usage: unset [-f] [-v] [-n] [name ...]\n", 2);
			return (2);
		}
		if (!is_valid_varname_unset(name))
			exit_status = 0;
		else
			remove_envp_var(name, envp_vars);
		args++;
	}
	return (exit_status);
}

int	numb_com(char *str)
{
	int	flag;
	int	pipes;

	pipes = 0;
	flag = 0;
	while (*str)
	{
		if (flag == 0 && (*str == '"' || *str == '\''))
			flag = 1;
		else if (flag == 1 && (*str == '"' || *str == '\''))
			flag = 0;
		else if (*str == '|' && flag == 0)
			pipes++;
		str++;
	}
	return (pipes + 1);
}
