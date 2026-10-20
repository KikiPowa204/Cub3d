/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 10:25:44 by knajmech          #+#    #+#             */
/*   Updated: 2025/10/21 09:30:40 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	counter;

	counter = 0;
	if (size)
	{
		while (counter < size - 1 && src[counter])
		{
			dst[counter] = src[counter];
			counter++;
		}
		dst[counter] = '\0';
	}
	return (ft_strlen(&src[counter]) + counter);
}
//#include <stdio.h>
//#include <bsd/string.h>
/*int main(void)
{
	char string[20] = "Hello world 42";
	char string2[20] = "Hello world 42";

	printf("%zu %zu", ft_strlcpy(string, string+2, 4), 
	strlcpy(string2, string2+2, 4));
	
}*/
