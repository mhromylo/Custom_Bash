/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhromylo <mhromylo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 15:53:05 by mhromylo          #+#    #+#             */
/*   Updated: 2024/04/30 11:43:55 by mhromylo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	non_subj(char *input)
{
	if (*input == '\\' || *input == ';')
	{
		ft_putstr_fd("not required by the subject\n", 2);
		return (1);
	}
	return (0);
}

int	chek_input(char *input)
{
	if (start_pipe(input))
		return (1);
	if (redir_empty(input))
		return (1);
	if (empty_pipe(input))
		return (1);
	return (0);
}

int	first_quote(char *str)
{
	if (non_subj(str))
		return (1);
	if (*str == '"')
	{
		str++;
		while (*str != '"')
		{
			if (*str != ' ')
				return (0);
			str++;
		}
		return (1);
	}
	else if (*str == '\'')
	{
		str++;
		while (*str != '\'')
		{
			if (*str != ' ')
				return (0);
			str++;
		}
		return (1);
	}
	return (0);
}

int	ft_exit_quote(char *str)
{
	int	i;

	i = 0;
	if (!ft_strncmp(str, "exit", 4))
	{
		while (*str && *str != '"')
			str++;
		if (*str && *str == '"')
		{
			i++;
			str++;
		}
		while (*str && *str != '"')
		{
			return (0);
			str++;
		}
		if (i == 1)
			return (1);
	}
	return (0);
}

int	invalid_input(char *input, int *exit_status, t_envp *envp_vars)
{
	int	result;

	result = 0;
	if (is_empty(input))
		result = 1;
	if (first_quote(input))
	{
		ft_putstr_fd("permission denied:\n", 2);
		*exit_status = 127;
		result = 1;
	}
	if (ft_exit_quote(input))
	{
		print_error_msg("exit", " numeric argument required");
		exit(2);
	}
	else if (open_quotes(input))
		result = 1;
	else if (chek_input(input))
		exit(2);
	else if (make_heredoc(input, envp_vars, exit_status) == 0)
		result = 1;
	if (result == 1)
		free (input);
	return (result);
}
