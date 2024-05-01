/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhromylo <mhromylo@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:32:14 by mhromylo          #+#    #+#             */
/*   Updated: 2023/11/22 12:50:19 by mhromylo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (haystack[i] != '\0' && i < len)
	{
		if (haystack[i] == needle[0])
		{
			while (needle[j] != '\0' && haystack[i + j] == needle[j]
				&& j + i < len)
			{
				if (needle[j + 1] == '\0')
					return ((char *)&haystack[i]);
				j++;
			}
		}
		i++;
	}
	return (NULL);
}
/*int	main(int argc, char const *argv[])
{
	char *s1 = "oh no not the empty string !";
        char *s2 = "";
        size_t max = 0;
        char *i1 = strnstr(s1, s2, max);
        char *i2 = ft_strnstr(s1, s2, max);

	printf("%s\n", i1);
	printf("%s\n", i2);

	return 0;
}*/
