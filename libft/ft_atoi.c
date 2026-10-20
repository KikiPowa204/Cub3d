/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 12:50:45 by knajmech          #+#    #+#             */
/*   Updated: 2026/02/24 13:59:38 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	atoi_valid(char *nptr)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(nptr);
	if (nptr[i] == '-' || nptr[i] == '+')
		i++;
	while (i < len)
	{
		if (nptr[i] > '9' || nptr[i] < '0')
			return (-1);
		i++;
	}
	return (1);
}

long	ft_atoi(char *nptr)
{
	long int	new;
	int			i;
	int			neg_switch;

	neg_switch = 0;
	new = 0;
	i = 0;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			neg_switch = 1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		new += nptr[i] - '0';
		i++;
		if (nptr[i] <= '9' && nptr[i] >= '0')
			new *= 10;
	}
	if (neg_switch)
		new *= -1;
	return (new);
}
