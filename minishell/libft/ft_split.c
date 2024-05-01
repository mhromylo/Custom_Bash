/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhromylo <mhromylo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:35:41 by mhromylo          #+#    #+#             */
/*   Updated: 2024/04/26 12:38:07 by mhromylo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_wordcount(char const *s, char c)
{
	size_t	i;

	i = 0;
	if (!*s)
		return (0);
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			i++;
		while (*s != c && *s)
			s++;
	}
	return (i);
}

static char	**make_arr(char const *s, char c)
{
	char	**splited;

	if (!s)
		return (NULL);
	splited = (char **)malloc ((ft_wordcount(s, c) + 1) * sizeof(char *));
	if (!splited)
		return (NULL);
	return (splited);
}

char	**ft_split(char const *s, char c)
{
	char	**splited;
	size_t	wlen;
	int		i;

	i = 0;
	splited = make_arr(s, c);
	if (!splited)
		return (NULL);
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
		{
			if (!ft_strchr(s, c))
				wlen = ft_strlen(s);
			else
				wlen = ft_strchr(s, c) - s;
			splited[i++] = ft_substr (s, 0, wlen);
			s += wlen;
		}
	}
	splited[i] = NULL;
	return (splited);
}
