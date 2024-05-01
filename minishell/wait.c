/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhromylo <mhromylo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:37:33 by mhromylo          #+#    #+#             */
/*   Updated: 2024/04/30 11:41:51 by mhromylo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_control_c(int status)
{
	return (WTERMSIG(status) == SIGINT);
}

static int	is_control_slash(int status)
{
	return (WTERMSIG(status) == SIGQUIT);
}

static int	handle_signal_interrupt(int status, int is_last_child)
{
	if (is_control_c(status))
		ft_putstr_fd("\n", STDOUT_FILENO);
	if (is_control_slash(status) && is_last_child)
		ft_putstr_fd("Quit\n", STDOUT_FILENO);
	return (128 + WTERMSIG(status));
}

int	wait_for_child(int child_pid, int is_last_child)
{
	int	status;

	if (child_pid == -1)
		return (1);
	if (waitpid(child_pid, &status, 0) == -1)
		print_perror_msg("waitpid", ft_itoa(child_pid));
	if (WIFSIGNALED(status))
		return (handle_signal_interrupt(status, is_last_child));
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_FAILURE);
}

int	wait_for_children(int *children_pid)
{
	int	i;
	int	exit_status;
	int	is_last_child;

	is_last_child = 0;
	i = 0;
	exit_status = 0;
	while (children_pid[i] != 0)
	{
		if (children_pid[i + 1] == 0)
			is_last_child = 1;
		exit_status = wait_for_child(children_pid[i], is_last_child);
		i++;
	}
	close_extra_fds();
	free(children_pid);
	return (exit_status);
}
