/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhromylo <mhromylo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:13:38 by mhromylo          #+#    #+#             */
/*   Updated: 2024/03/29 15:53:28 by mhromylo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char const	*find;

	find = NULL;
	while (*s)
	{
		if (*s == ((char)c))
			find = s;
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	else
		return ((char *)find);
}
