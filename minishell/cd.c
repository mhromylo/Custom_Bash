/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochurko <ochurko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 11:45:05 by mhromylo          #+#    #+#             */
/*   Updated: 2024/04/26 18:47:59 by ochurko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_cd_err_msg(char *command, char *msg, int i)
{
	if (i == 1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(command, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(msg, STDERR_FILENO);
		ft_putstr_fd(" No such file or directory\n", STDERR_FILENO);
	}
	else
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putstr_fd("too many arguments\n", STDERR_FILENO);
	}
	return (1);
}

int	pwd(void)
{
	char	cwd[4096];

	getcwd(cwd, 4096);
	ft_putstr_fd(cwd, 1);
	ft_putstr_fd("\n", 1);
	return (0);
}

static char	*make_path(char **args, t_envp *envp_vars, char **pwd_env)
{
	char	*path;

	if (args[1] && !str_equal(args[1], "~"))
	{
		if (args[1][0] == '~')
		{
			*pwd_env = ft_strjoin(envp_val("HOME", envp_vars), args[1] + 1);
			path = *pwd_env;
		}
		else if (args[1][0] == '-' && args[1][1] == '-')
			path = envp_val("HOME", envp_vars);
		else
			path = args[1];
	}
	else
		path = envp_val("HOME", envp_vars);
	return (path);
}

void	ft_envp_update(char *str, t_envp *envp_vars)
{
	char	*pwd_env;
	char	cwd[4096];

	pwd_env = envp_val("PWD", envp_vars);
	if (str_equal(str, "-"))
	{
		chdir(envp_val("OLDPWD", envp_vars));
		envp_update("OLDPWD", pwd_env, envp_vars);
		envp_update("PWD", getcwd(cwd, 4096), envp_vars);
		getcwd(cwd, 4096);
		ft_putstr_fd(cwd, 1);
		ft_putstr_fd("\n", 1);
	}
	else
	{
		if (envp_val("OLDPWD", envp_vars) && pwd_env && *pwd_env)
			envp_update("OLDPWD", pwd_env, envp_vars);
		if (pwd_env && *pwd_env)
			envp_update("PWD", getcwd(cwd, 4096), envp_vars);
	}
}

int	cd(char **args, t_envp *envp_vars)
{
	char	*pwd_env;

	pwd_env = NULL;
	if (args[1] && args[2] && (!ft_atoi(args[2]) || ft_atoi(args[2]) > 1023))
		return (print_cd_err_msg("cd", args[1], 0));
	if (chdir(make_path(args, envp_vars, &pwd_env))
		!= 0 && !str_equal(args[1], "-"))
		return (print_cd_err_msg("cd", args[1], 1));
	if (pwd_env)
		free(pwd_env);
	ft_envp_update(args[1], envp_vars);
	return (0);
}
