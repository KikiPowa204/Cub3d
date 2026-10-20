/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 12:30:16 by knajmech          #+#    #+#             */
/*   Updated: 2025/10/07 09:28:55 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*val_1;
	const unsigned char	*val_2;

	val_1 = (const unsigned char *)s1;
	val_2 = (const unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (val_1[i] != val_2[i])
			return (val_1[i] - val_2[i]);
		i++;
	}
	return (0);
}
