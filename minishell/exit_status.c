/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochurko <ochurko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:03:20 by mhromylo          #+#    #+#             */
/*   Updated: 2024/04/24 16:18:14 by ochurko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_last_exit_status_var_pos(char *input)
{
	while (input && *input)
	{
		if (*input == '\'')
		{
			input++;
			while (*input && *input != '\'')
				input++;
		}
		if (*input == '"')
		{
			input++;
			while (*input && *input != '"')
			{
				if (*input == '$' && input[1] == '?')
					return (input);
				input++;
			}
		}
		if (*input == '$' && input[1] == '?')
			return (input);
		input++;
	}
	return (NULL);
}

static void	update_input(char **input, char *exit_code, char *second_part)
{
	char	*first_part;
	char	*updated;

	first_part = ft_strjoin(*input, exit_code);
	updated = ft_strjoin(first_part, second_part);
	free(*input);
	free(first_part);
	*input = updated;
}

void	get_last_exit_status(char **input, int exit_status)
{
	char	*last_exit_status_var_pos;
	char	*exit_status_str;

	last_exit_status_var_pos = get_last_exit_status_var_pos(*input);
	if (last_exit_status_var_pos)
	{
		*last_exit_status_var_pos = '\0';
		exit_status_str = ft_itoa(exit_status);
		update_input(input, exit_status_str, (last_exit_status_var_pos + 2));
		free(exit_status_str);
		get_last_exit_status(input, exit_status);
	}
}
