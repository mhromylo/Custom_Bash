/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhromylo <mhromylo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:25:24 by mhromylo          #+#    #+#             */
/*   Updated: 2024/04/26 16:08:53 by mhromylo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	declare(t_envp *envp_vars)
{
	t_envp	*tmp;

	tmp = envp_vars;
	while (tmp)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(tmp->name_env, STDOUT_FILENO);
		if (tmp->val_env)
		{
			ft_putstr_fd("=", STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
			ft_putstr_fd(tmp->val_env, STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
		}
		ft_putstr_fd("\n", STDOUT_FILENO);
		tmp = tmp->next;
	}
	return (0);
}

void	print_varname_err_msg(char *command, char *name)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(command, STDERR_FILENO);
	ft_putstr_fd(": '", STDERR_FILENO);
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putstr_fd(": invalid parameter name\n", STDERR_FILENO);
}

static int	print_built_err_msg(char *command, char *name, int error)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(command, STDERR_FILENO);
	ft_putstr_fd(": `", STDERR_FILENO);
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
	return (error);
}

static int	minus_name(char *name)
{
	if (*name == '=')
	{
		ft_putstr_fd("name not found\n", STDERR_FILENO);
		return (1);
	}
	else if (*name == '-')
	{
		return (print_built_err_msg("export", name, 2));
	}
	while (*name)
	{
		name++;
		if (*name == '-')
		{
			return (print_built_err_msg("export", name, 1));
		}
	}
	return (0);
}

int	export(char **args, t_envp **envp_vars)
{
	char	*only_name;
	int		exit_status;
	int		i;

	i = 1;
	if (!args[i])
		return (declare(*envp_vars));
	while (args[i])
	{
		only_name = get_name(args[i]);
		if (args[i][0] == '=' || (args[i][0] >= '0' && args[i][0] <= '9'))
		{
			free(only_name);
			return (print_built_err_msg(args[0], args[i], 1));
		}
		exit_status = minus_name(only_name);
		if (exit_status != 0)
		{
			free(only_name);
			return (exit_status);
		}
		exit_status = exp_rout(only_name, envp_vars, args[i], exit_status);
		i++;
	}
	return (exit_status);
}
