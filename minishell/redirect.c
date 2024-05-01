/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhromylo <mhromylo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 15:12:52 by mhromylo          #+#    #+#             */
/*   Updated: 2024/04/26 17:57:18 by mhromylo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	invalid_token(char c)
{
	if (c == '|')
		return (1);
	if (c == '>')
		return (1);
	if (c == '<')
		return (1);
	return (0);
}

char	get_next_redir(char *str)
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
		if (*str == '<' || *str == '>' || *str < 0)
			return (*str);
		str++;
	}
	return (0);
}

static char	*get_redir_pos(char *str, char redir)
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
		if (*str == redir)
			return (str);
		str++;
	}
	return (NULL);
}

static int	invalid_redir(char *input)
{
	if (input[0] == '<' && input[1] == '<')
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("syntax error near unexpected token '<'\n", 2);
		return (1);
	}
	else if (input[0] == '>' && input[1] == '>')
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("syntax error near unexpected token '>'\n", 2);
		return (1);
	}
	input[1] = '\0';
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("syntax error near unexpected token '>'\n", 2);
	return (1);
}

int	redir_empty(char *input)
{
	char	*red_pos;
	char	next_redir;

	next_redir = get_next_redir(input);
	red_pos = get_redir_pos(input, next_redir);
	if (!red_pos)
		return (0);
	if (red_pos[0] == '<' && red_pos[1] == '<')
		red_pos++;
	else if (red_pos[0] == '>' && (red_pos[1] == '>' || red_pos[1] == '|'))
		red_pos++;
	red_pos++;
	while (*red_pos == ' ' || *red_pos == '\t')
		red_pos++;
	if (*red_pos == '\0')
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("syntax error near unexpected token '>'\n", 2);
		return (1);
	}
	if (invalid_token(*red_pos))
		return (invalid_redir(red_pos));
	return (redir_empty(red_pos));
	return (1);
}
