/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 12:24:58 by knajmech          #+#    #+#             */
/*   Updated: 2025/10/20 18:04:35 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*val;

	val = (const unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (val[i] == (unsigned char)c)
			return ((void *)&val[i]);
		i++;
	}
	return (0);
}

/*int main(void)
{
	char string[] = "Hello world 42";

	printf("%p %p", ft_memchr(string, '4', 15), memchr(string, '4', 15)); 
}*/
