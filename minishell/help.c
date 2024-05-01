/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhromylo <mhromylo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 18:40:14 by mhromylo          #+#    #+#             */
/*   Updated: 2024/04/29 18:41:14 by mhromylo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	restore_original_fds(int original_fds[2])
{
	redirect_fd(original_fds[0], 0);
	redirect_fd(original_fds[1], 1);
}

void	restore_original_fds_one(int orig_fds[2])
{
	if (orig_fds[0] != -1)
		redirect_fd(orig_fds[0], 0);
	if (orig_fds[1] != -1)
		redirect_fd(orig_fds[1], 1);
}

int	redirect_input_one(char *command, int orig_fds[2], t_envp **envp_vars)
{
	if (orig_fds[0] == -1)
		orig_fds[0] = dup(0);
	if (redirect_input(command, envp_vars) == 0)
	{
		redirect_fd(orig_fds[0], 0);
		return (0);
	}
	return (1);
}

int	redirect_output_one(char *command, int orig_fds[2])
{
	if (orig_fds[1] == -1)
		orig_fds[1] = dup(1);
	if (redirect_output(command) == 0)
	{
		redirect_fd(orig_fds[1], 1);
		return (0);
	}
	return (1);
}

int	ft_issymb(char *name, t_envp *envp_vars)
{
	t_envp	*tmp;

	tmp = envp_vars;
	while (tmp)
	{
		if (str_equal(name, tmp->val_env))
		{
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
