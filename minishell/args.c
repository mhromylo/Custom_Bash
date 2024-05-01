/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhromylo <mhromylo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:02:20 by mhromylo          #+#    #+#             */
/*   Updated: 2024/04/26 12:40:00 by mhromylo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	here_qoute(char *str)
{
	if (!str)
		return (0);
	while (str && *str)
	{
		if (*str == '\'' || *str == '"')
			return (1);
		str++;
	}
	return (0);
}

static void	replace_char(char *str, char quote, char c)
{
	while (*str && *str != quote)
		str++;
	if (*str)
		str++;
	while (*str && *str != quote)
	{
		if (*str == c)
			*str = -1;
		str++;
	}
	if (*str)
		str++;
	if (*str)
		replace_char(str, quote, c);
}

static void	remove_quotes(char *str)
{
	char	quote;

	quote = 0;
	while (*str && !quote)
	{
		if (*str == '\'' || *str == '"')
		{
			quote = *str;
			ft_memmove(str, str + 1, ft_strlen(str + 1) + 1);
		}
		else
			str++;
	}
	while (*str && quote)
	{
		if (*str && *str == quote)
		{
			quote = 0;
			ft_memmove(str, str + 1, ft_strlen(str + 1) + 1);
		}
		else
			str++;
	}
	if (*str)
		return (remove_quotes(str));
}

static void	restore_spaces(char **exec_args)
{
	char	*str;

	while (*exec_args)
	{
		str = *exec_args;
		while (*str)
		{
			if (*str == -1)
				*str = ' ';
			str++;
		}
		exec_args++;
	}
	return ;
}

char	**split_args(char *comand)
{
	char	**exec_args;

	ft_replace_t(comand);
	if (!here_qoute(comand))
		return (ft_split(comand, ' '));
	replace_char(comand, '"', ' ');
	replace_char(comand, '\'', ' ');
	remove_quotes(comand);
	exec_args = ft_split(comand, ' ');
	restore_spaces(exec_args);
	return (exec_args);
}
