/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 10:54:09 by knajmech          #+#    #+#             */
/*   Updated: 2025/10/21 09:29:58 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	counter_dst;
	size_t	counter_src;
	size_t	len_dst;
	size_t	len_src;

	len_dst = 0;
	counter_dst = 0;
	counter_src = 0;
	while (len_dst < size && dst[len_dst])
		len_dst++;
	len_src = ft_strlen(src);
	if ((size_t)ft_strlen(dst) >= size)
		return (len_dst + len_src);
	while (len_dst + counter_dst + 1 < size && src[counter_src])
	{
		dst[len_dst + counter_dst] = src[counter_src];
		counter_dst++;
		counter_src++;
	}
	dst[len_dst + counter_dst] = '\0';
	return (len_dst + len_src);
}
//#include <bsd/string.h>
//#include <stdio.h>
/*
static int main(void)
{
	char dst[80] = "cat & dog\0a123456789";
	char dst2[80] = "cat & dog\0a123456789";
	size_t size = 15;

	printf("%zd",strlcat(dst2+2, dst2, size));	
	printf("%zd",ft_strlcat(dst+2, dst, size));
}*/
