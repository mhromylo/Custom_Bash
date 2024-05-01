/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochurko <ochurko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 13:10:55 by mhromylo          #+#    #+#             */
/*   Updated: 2024/04/26 18:18:22 by ochurko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_varname(char c)
{
	return (ft_isalnum(c) || c == '_');
}

int	is_valid_varname(char *name)
{
	while (*name)
	{
		if (!is_varname(*name))
			return (0);
		name++;
	}
	return (1);
}

static char	*find_var_pos(char *input)
{
	while (*input)
	{
		if (*input == '\'')
		{
			input++;
			while (*input && *input != '\'')
				input++;
		}
		if (*input == '\"')
		{
			input++;
			while (*input && *input != '\"')
			{
				if (*input == '$' && is_varname(input[1]))
					return (input);
				input++;
			}
		}
		if (*input == '$' && is_varname(input[1]))
			return (input);
		input++;
	}
	return (NULL);
}

char	*update_input(char **input, char *var_val, char *second_part)
{
	char	*first_part;
	char	*updated;

	if (!*input[0] && !var_val)
		first_part = ft_strdup("");
	else if (!*input[0] && var_val)
		first_part = ft_strdup(var_val);
	else if (!var_val)
		first_part = ft_strdup(*input);
	else
		first_part = ft_strjoin(*input, var_val);
	updated = ft_strjoin(first_part, second_part);
	free(first_part);
	free(*input);
	return (updated);
}

void	variables(char **input, t_envp *envp_vars)
{
	char	*var_pos;
	char	*var_name;
	char	*var_value;
	int		i;

	var_pos = find_var_pos(*input);
	if (var_pos)
	{
		i = 0;
		while (is_varname(var_pos[i + 1]))
			i++;
		var_name = ft_substr(var_pos + 1, 0, i);
		*var_pos = '\0';
		var_value = envp_val(var_name, envp_vars);
		*input = update_input(input, var_value, (var_pos + 1 + i));
		free(var_name);
		variables(input, envp_vars);
	}
}
