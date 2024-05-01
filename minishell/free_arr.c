/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_arr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhromylo <mhromylo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:50:10 by mhromylo          #+#    #+#             */
/*   Updated: 2024/04/26 16:14:45 by mhromylo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_arr(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}

int	get_name_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] != ' ' && str[i] != '|' && str[i] != '\t' && str[i] != '>'
		&& str[i] != '<' && str[i])
	{
		if (str[i] == '\'')
		{
			while (str[++i] != '\'')
				;
			i++;
		}
		else if (str[i] == '"')
		{
			while (str[++i] != '"')
			{
				if (str[i] == '\\')
					i++;
			}
			i++;
		}
		else
			i++;
	}
	return (i);
}

void	make_filename(char *src, char *dst, int i, int k)
{
	while (src[i] != ' ' && src[i] != '|' && src[i] != '\t' && src[i] != '>'
		&& src[i] != '<' && src[i])
	{
		if (src[i] == '\'')
		{
			while (src[++i] != '\'')
				dst[k++] = src[i];
			i++;
		}
		else if (src[i] == '"')
		{
			while (src[++i] != '"')
			{
				if (src[i] == '\\')
					i++;
				dst[k++] = src[i];
			}
			i++;
		}
		else
			dst[k++] = src[i++];
	}
	dst[k] = '\0';
}

char	*ft_file_name(char *str)
{
	int		i;
	char	*filename;

	i = get_name_len(str);
	filename = malloc((i + 1) * sizeof(char));
	if (!filename)
		return (0);
	make_filename(str, filename, 0, 0);
	return (filename);
}
