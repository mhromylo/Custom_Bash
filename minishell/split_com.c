/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_com.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochurko <ochurko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:04:45 by mhromylo          #+#    #+#             */
/*   Updated: 2024/04/29 11:49:06 by ochurko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_p(char const *s1, char s2)
{
	size_t	size1;
	size_t	i;
	char	*res;

	i = 0;
	size1 = ft_strlen(s1);
	res = (char *)malloc(sizeof(char) * (size1 + 2));
	if (!res)
		return (0);
	while (i < size1)
	{
		res[i] = s1[i];
		i++;
	}
	res[i] = s2;
	i++;
	res[i] = '\0';
	free((void *)s1);
	return (res);
}

char	*ft_len_com(char *str, int *len)
{
	int		i;
	char	*com_str;
	int		flag;

	flag = 0;
	i = 0;
	com_str = malloc(sizeof(char));
	com_str[0] = '\0';
	while (str[i] != '\0')
	{
		if (flag == 0 && (str[i] == '"' || str[i] == '\''))
			flag = 1;
		else if (flag == 1 && (str[i] == '"' || str[i] == '\''))
			flag = 0;
		if (str[i] == '|' && flag == 0)
			break ;
		else
		{
			com_str = ft_strjoin_p(com_str, str[i]);
			*len = *len + 1;
		}
		i++;
	}
	return (com_str);
}

int	ft_copy_command(char **commands, char *com_str, int len, int *i)
{
	*i += 1;
	commands[*i] = malloc(sizeof(char) * len + 1);
	if (!commands[*i])
	{
		free(com_str);
		free_arr(commands);
		return (0);
	}
	if (!ft_strlcpy(commands[*i], com_str, len + 1))
		return (0);
	return (1);
}

char	**split_commands(char *str, int len)
{
	char	**commands;
	char	*com_str;
	int		i;

	i = -1;
	commands = malloc(sizeof(char *) * (numb_com(str) + 1));
	if (!commands)
		return (0);
	while (*str)
	{
		if (len == 0 && *str != ' ')
			com_str = ft_len_com(str, &len);
		if (len != 0)
		{
			if (!ft_copy_command(commands, com_str, len, &i))
				return (0);
			str += len;
			len = 0;
			free(com_str);
		}
		if (*str)
			str++;
	}
	commands[++i] = NULL;
	return (commands);
}
