/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochurko <ochurko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:28:19 by mhromylo          #+#    #+#             */
/*   Updated: 2024/04/24 11:43:03 by ochurko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	isspase(int c)
{
	if ((c > 8 && c < 14) || (c == 32))
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	nb;
	int	minus;

	nb = 0;
	minus = 1;
	while (*str && isspase(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			minus *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		nb = nb * 10 + minus * (*str - 48);
		str++;
	}
	return (nb);
}
