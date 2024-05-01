/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhromylo <mhromylo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:34:58 by mhromylo          #+#    #+#             */
/*   Updated: 2024/04/26 16:10:12 by mhromylo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_extra_fds(void)
{
	int	last_open_fd;

	last_open_fd = open("/tmp/last_fd", O_RDWR | O_CREAT, 0666);
	if (last_open_fd == -1)
		print_perror_msg("open", "/tmp/last_fd");
	while (last_open_fd > 2)
	{
		close(last_open_fd);
		last_open_fd--;
	}
}

void	close_all_fds(void)
{
	close_extra_fds();
	close(0);
	close(1);
	close(2);
}

void	clean_after_execute(int *children_pid)
{
	close_extra_fds();
	free(children_pid);
}

void	external_exit(char **args, t_envp *envp_vars, int exit_status)
{
	if (exit_status == 126)
		print_error_msg(args[0], "Is a directory");
	if (exit_status == 127)
		print_error_msg(args[0], "command not found");
	rl_clear_history();
	free_t_envp(&envp_vars);
	free_arr(args);
	close_all_fds();
	exit(exit_status);
}

int	is_path(char *command)
{
	if (*command == '.')
		command++;
	if (*command == '.')
		command++;
	if (*command == '/')
		return (1);
	return (0);
}
