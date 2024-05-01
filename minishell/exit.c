/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhromylo <mhromylo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 15:30:28 by mhromylo          #+#    #+#             */
/*   Updated: 2024/04/26 17:56:19 by mhromylo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exit_error(char **args, int error)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(args[0], STDERR_FILENO);
	ft_putstr_fd(":", STDERR_FILENO);
	free_arr(args);
	if (error == 1)
		ft_putstr_fd(" too many arguments\n", STDERR_FILENO);
	else
		ft_putstr_fd(" numeric argument required\n", STDERR_FILENO);
	exit(error);
}

int	built_exit(char **args, int exit_status)
{
	if (!args[1])
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		exit(exit_status);
		return (exit_status);
	}
	if (args[2] != NULL)
	{
		if (!ft_atoi(args[1]) && ft_strcmp(args[1], "0"))
			exit_error(args, 2);
		exit_error(args, 1);
	}
	if (!ft_atoi(args[1]) && ft_strcmp(args[1], "0"))
		exit_error(args, 2);
	if (args[1])
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		exit(ft_atoi(args[1]));
		return (ft_atoi(args[1]));
		free_arr(args);
	}
	return (EXIT_FAILURE);
}

int	make_index(char *com, int j)
{
	if (com[j] == '<' && com[j + 1] == '<')
	{
		j += 2;
		while (com[j] == ' ')
			j++;
	}
	else
	{
		if (com[++j] == '>')
			j++;
		while (com[j] == ' ')
			j++;
	}
	if (com[j] == '"')
	{
		j++;
		while (com[j] != '"')
			j++;
		j++;
	}
	while (com[j] != ' ' && com[j] != '|' && com[j] != '\t' && com[j] != '>'
		&& com[j] != '<' && com[j])
		j++;
	return (j);
}

char	*ft_move_command(char *com, char red, int i, int j)
{
	char	*str;

	str = com;
	while (com[j] != red)
		str[i++] = com[j++];
	j = make_index(com, j);
	while (com[j])
		str[i++] = com[j++];
	str[i] = '\0';
	return (str);
}
