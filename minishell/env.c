/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochurko <ochurko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 16:54:25 by mhromylo          #+#    #+#             */
/*   Updated: 2024/04/26 15:42:48 by ochurko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env(t_envp *envp_vars, char **args)
{
	t_envp	*tmp;

	tmp = envp_vars;
	if (envp_val("PATH", tmp) == NULL || args[1])
	{
		print_error_msg("env", "No such file or directory");
		return (127);
	}
	else
	{
		while (tmp)
		{
			if (tmp->name_env)
			{
				ft_putstr_fd(tmp->name_env, 1);
				ft_putstr_fd("=", 1);
				ft_putstr_fd(tmp->val_env, 1);
				ft_putstr_fd("\n", 1);
			}
			tmp = tmp->next;
		}
	}
	return (0);
}
