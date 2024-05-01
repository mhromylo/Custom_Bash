/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhromylo <mhromylo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:17:14 by mhromylo          #+#    #+#             */
/*   Updated: 2024/04/30 11:53:26 by mhromylo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_one_command(char *command, t_envp **envp_vars)
{
	char	**args;
	int		exit_status;
	int		original_fds[2];

	exit_status = 0;
	if (!redirect_one_com(command, &original_fds[0], envp_vars, 0))
	{
		restore_original_fds_one(original_fds);
		free(command);
		return (1);
	}
	args = split_args(command);
	free(command);
	if (is_builtin(args[0]))
		exit_status = builtin(args, envp_vars, exit_status);
	else
		exit_status = execute_forked_external_one(args, *envp_vars);
	restore_original_fds_one(original_fds);
	free_arr (args);
	return (exit_status);
}

int	minishell(t_envp *envp_vars, int exit_status)
{
	char	*input;

	while (1)
	{
		define_main_signals();
		input = readline("MINISHEL> ");
		if (!input)
		{
			free_t_envp(&envp_vars);
			ft_putstr_fd("exit\n", 1);
			exit(exit_status);
		}
		add_history(input);
		if (invalid_input(input, &exit_status, envp_vars))
			continue ;
		variables(&input, envp_vars);
		get_last_exit_status(&input, exit_status);
		if (!has_pipe(input))
			exit_status = execute_one_command(input, &envp_vars);
		else
			exit_status = execute_multiple_command(input, &envp_vars);
	}
	return (exit_status);
}

int	main(int argc, char **argv, char **envp)
{
	int	exit_status;

	exit_status = 0;
	if (argv && argc > 1)
	{
		ft_putstr_fd("Minishell can't take arguments", 2);
		return (0);
	}
	return (minishell(init_envp(envp), exit_status));
}
