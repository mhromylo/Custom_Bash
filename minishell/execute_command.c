/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochurko <ochurko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 12:54:51 by ochurko           #+#    #+#             */
/*   Updated: 2024/04/29 13:18:22 by ochurko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	envp_size(t_envp *envp_vars)
{
	size_t	size;
	t_envp	*tmp;

	size = 0;
	tmp = envp_vars;
	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}
	return (size);
}

char	**minienv_to_envp(t_envp *envp_vars)
{
	char	**envp;
	t_envp	*tmp;
	int		i;

	envp = malloc(sizeof(char *) * (envp_size(envp_vars) + 1));
	tmp = envp_vars;
	i = 0;
	while (tmp)
	{
		envp[i] = ft_strjoin(ft_strjoin(tmp->name_env, "="), tmp->val_env);
		i++;
		tmp = tmp->next;
	}
	envp[i] = NULL;
	return (envp);
}

void	handle_execve_errors(char **args, char *path, char **envp)
{
	int		error;
	char	*s;

	s = *envp;
	error = 1;
	print_perror_msg("execve", args[0]);
	if (access(path, F_OK) != 0)
		error = 127;
	else if (access(path, X_OK) != 0)
		error = 126;
	if (args[0][0] == '.' || (args[0][0] == '.' && args[0][1] == '.'))
		error = 127;
	free_arr(args);
	free_arr(envp);
	free(path);
	exit(error);
}

int	execute_external(char **args, t_envp *envp_vars)
{
	char	*path;
	char	*command;
	char	**envp;

	command = args[0];
	if (is_empty(command))
		external_exit(args, envp_vars, 0);
	if (is_folder(command))
		external_exit(args, envp_vars, 126);
	path = get_path(command, envp_vars);
	if (path == NULL && envp_has_path(envp_vars))
		external_exit(args, envp_vars, 127);
	else if (path == NULL)
		path = ft_strdup(command);
	close_extra_fds();
	envp = minienv_to_envp(envp_vars);
	free_t_envp(&envp_vars);
	if (execve(path, args, envp) == -1)
		handle_execve_errors(args, path, envp);
	else
		free_arr(args);
	exit(0);
}

void	execute_command(char *command, char **commands, t_envp **envp_vars)
{
	char	**args;
	char	*s;
	t_envp	*f;

	f = *envp_vars;
	s = commands[0];
	close_extra_fds();
	args = split_args(command);
	free_arr(commands);
	if (is_builtin(args[0]))
		execute_forked_builtin(args, envp_vars);
	else
		execute_external(args, *envp_vars);
}
