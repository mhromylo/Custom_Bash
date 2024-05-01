/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochurko <ochurko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:49:32 by mhromylo          #+#    #+#             */
/*   Updated: 2024/04/26 18:48:14 by ochurko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	str_equal(const char *s1, const char *s2)
{
	size_t	i;

	if (!s1 || !s2)
		return (0);
	i = ft_strlen(s1);
	if (i != ft_strlen(s2))
		return (0);
	return (ft_strncmp(s1, s2, i) == 0);
}

int	is_builtin(char *command)
{
	if (!command)
		return (0);
	if (str_equal(command, "env"))
		return (1);
	if (str_equal(command, "export"))
		return (1);
	if (str_equal(command, "echo"))
		return (1);
	if (str_equal(command, "cd"))
		return (1);
	if (str_equal(command, "pwd"))
		return (1);
	if (str_equal(command, "unset"))
		return (1);
	if (str_equal(command, "exit"))
		return (1);
	return (0);
}

int	builtin(char **args, t_envp **envp_vars, int exit_status)
{
	char	*command;

	command = args[0];
	if (str_equal(command, "env"))
		return (env(*envp_vars, args));
	if (str_equal(command, "export"))
		return (export(args, envp_vars));
	if (str_equal(command, "echo"))
		return (echo(args));
	if (str_equal(command, "cd"))
		return (cd(args, *envp_vars));
	if (str_equal(command, "pwd"))
		return (pwd());
	if (str_equal(command, "unset"))
		return (unset(args, envp_vars));
	if (str_equal(command, "exit"))
		return (built_exit(args, exit_status));
	else
		return (EXIT_FAILURE);
}

void	ft_replace_t(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'')
				i++;
		}
		if (str[i] == '"')
		{
			i++;
			while (str[i] != '"')
				i++;
		}
		if (str[i] == '\t')
			str[i] = ' ';
		i++;
	}
}

int	execute_forked_builtin(char **args, t_envp **envp_vars)
{
	int	exit_status;

	exit_status = builtin(args, envp_vars, 0);
	free_arr(args);
	free_t_envp(envp_vars);
	rl_clear_history();
	exit(exit_status);
}
