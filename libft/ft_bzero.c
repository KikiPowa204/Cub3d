/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:50:02 by knajmech          #+#    #+#             */
/*   Updated: 2025/10/10 10:16:04 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			counter;
	unsigned char	*val;

	val = (unsigned char *)s;
	counter = 0;
	while (counter < n)
	{
		val[counter] = 0;
		counter++;
	}
}
