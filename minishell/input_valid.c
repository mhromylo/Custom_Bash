/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_valid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochurko <ochurko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 16:13:32 by mhromylo          #+#    #+#             */
/*   Updated: 2024/04/19 11:13:33 by ochurko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_empty(char *str)
{
	if (!str)
		return (1);
	while (*str)
	{
		if (*str != ' ')
			return (0);
		str++;
	}
	return (1);
}

int	start_pipe(char *input)
{
	if (input[0] == '|')
	{
		ft_putstr_fd("parse error near `|'\n", 2);
		return (1);
	}
	return (0);
}

char	*get_next_pipe(char *str)
{
	while (*str)
	{
		if (*str == '\'')
		{
			str++;
			while (*str != '\'')
				str++;
		}
		if (*str == '"')
		{
			str++;
			while (*str != '"')
				str++;
		}
		if (*str == '|')
			return (str);
		str++;
	}
	return (NULL);
}

int	empty_pipe(char *input)
{
	char	*next_pipe;

	next_pipe = get_next_pipe(input);
	if (!next_pipe)
		return (0);
	next_pipe++;
	while (*next_pipe == ' ' || *next_pipe == '\t')
		next_pipe++;
	if (*next_pipe == '|')
	{
		ft_putstr_fd("Error! | whithout args\n", 2);
		return (1);
	}
	return (empty_pipe(next_pipe));
}

int	open_quotes(char *str)
{
	char	quote;

	quote = 0;
	while (*str && !quote)
	{
		if (*str == '\'' || *str == '"')
			quote = *str;
		str++;
	}
	while (*str && quote)
	{
		if (*str && *str == quote)
			quote = 0;
		str++;
	}
	if (*str)
		return (open_quotes(str));
	else if (!quote)
		return (0);
	else
	{
		ft_putstr_fd("We Not interpret unclosed quotes\n", STDERR_FILENO);
		return (1);
	}
}
