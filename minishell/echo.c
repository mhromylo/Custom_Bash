/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochurko <ochurko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:27:43 by mhromylo          #+#    #+#             */
/*   Updated: 2024/04/26 18:48:26 by ochurko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(char **args)
{
	int	i;
	int	n;

	n = 1;
	i = 1;
	if (args[1] && ft_strncmp(args[1], "-n", 3) == 0)
	{
		n = 0;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (n)
		ft_putstr_fd("\n", 1);
	return (0);
}

int	is_folder(char *command)
{
	struct stat	statbuf;

	if (*command == '~')
		return (1);
	if (stat(command, &statbuf) != 0)
		return (0);
	if (S_ISDIR(statbuf.st_mode))
	{
		if (*command == '.')
			command++;
		if (*command == '.')
			command++;
		if (*command == '/')
			return (1);
	}
	return (0);
}
