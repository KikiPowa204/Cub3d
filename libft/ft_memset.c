/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:38:03 by knajmech          #+#    #+#             */
/*   Updated: 2025/10/21 09:28:11 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			counter;
	unsigned char	*val;

	val = (unsigned char *) s;
	counter = 0;
	while (counter < n)
	{
		val[counter] = c;
		counter++;
	}
	return (s);
}
//#include <string.h>
//#include <stdio.h>  *int main(void)
/*
{
	char str[] = "dog";
	char str2[] = "dog";
	char *ptr = ft_memset(str, 's', 3);
	char *ptr2 =  memset(str2, 's', 3);
	printf("%s\n%s", ptr, ptr2);
}*/
