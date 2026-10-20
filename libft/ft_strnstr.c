/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 12:36:40 by knajmech          #+#    #+#             */
/*   Updated: 2025/10/21 09:31:42 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	j = ft_strlen(little);
	i = 0;
	if (!j)
		return ((char *)big);
	while (big[i] && (i <= len - j))
	{
		if (big[i] == little[0] && big[i + j -1] == little[j - 1])
		{
			if ((i + j) > len)
				return (0);
			if (!ft_strncmp(big + i, little, j))
				return ((char *)&big[i]);
		}
		i++;
	}
	return (0);
}
//#include <bsd/string.h>
//#include <stdio.h>
/*
static int main(void)
{
	char str[] = "Hello world. 42 is the answer to the universe, 
	to everything, based on hitchhiker's guide to the galaxy";

	printf("%p %p", ft_strnstr(str, "world", 150), strnstr(str, "world", 150));
}*/
