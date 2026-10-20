/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 10:22:21 by knajmech          #+#    #+#             */
/*   Updated: 2025/10/21 09:54:17 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static void	*launch(unsigned char *dest, unsigned const char *src, size_t n)
{
	size_t	counter;

	if (dest > src)
	{
		counter = n - 1;
		while (counter > 0)
		{
			dest[counter] = src[counter];
			counter--;
		}
		dest[counter] = src[counter];
	}
	else
	{
		counter = 0;
		while (counter < n)
		{
			dest[counter] = src[counter];
			counter++;
		}
	}
	return (dest);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*val_dest;
	const unsigned char	*val_src;

	if (!n)
		return (dest);
	else if (n && (!dest && !src))
		return (0);
	val_dest = (unsigned char *) dest;
	val_src = (const unsigned char *)src;
	dest = launch(val_dest, val_src, n);
	return (dest);
}
