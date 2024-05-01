/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhromylo <mhromylo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 15:27:27 by mhromylo          #+#    #+#             */
/*   Updated: 2024/04/26 16:11:23 by mhromylo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_path(char *base, char *part1, char *part2, char *part3)
{
	*base = 0;
	ft_strlcat(base, part1, 2048);
	ft_strlcat(base, part2, 2048);
	ft_strlcat(base, part3, 2048);
}

char	*local_path(char *command, t_envp *envp_vars)
{
	char	full_path[2048];

	if (*command == '/')
		return (ft_strdup(command));
	full_path[0] = 0;
	create_path(full_path, envp_val("PWD", envp_vars), "/", command);
	return (ft_strdup(full_path));
}

char	*get_path(char *command, t_envp *envp_vars)
{
	char	*path_env;
	char	**paths;
	char	current_path[2048];
	char	**paths_start;

	current_path[0] = 0;
	if (is_path(command))
		return (local_path(command, envp_vars));
	path_env = envp_val("PATH", envp_vars);
	paths = ft_split(path_env, ':');
	paths_start = paths;
	while (paths && *paths)
	{
		create_path(current_path, *paths, "/", command);
		if (access(current_path, F_OK) == 0)
		{
			free_arr(paths_start);
			return (ft_strdup(current_path));
		}
		paths++;
	}
	free_arr(paths_start);
	return (NULL);
}

int	envp_has_path(t_envp *envp_vars)
{
	if (envp_val("PATH", envp_vars) != NULL)
		return (1);
	return (0);
}
