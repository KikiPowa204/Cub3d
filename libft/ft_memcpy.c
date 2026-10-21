/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 09:29:03 by knajmech          #+#    #+#             */
/*   Updated: 2025/10/21 15:24:02 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				counter;
	unsigned char		*val_dest;
	const unsigned char	*val_src;

	counter = 0;
	val_dest = (unsigned char *) dest;
	val_src = (const unsigned char *) src;
	while (counter < n)
	{
		val_dest[counter] = val_src[counter];
		counter++;
	}
	return (dest);
}
