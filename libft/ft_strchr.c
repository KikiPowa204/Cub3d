/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 12:06:09 by knajmech          #+#    #+#             */
/*   Updated: 2025/10/20 16:37:49 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*pos;
	size_t	i;
	char	cast;

	cast = (char) c;
	pos = (char *)s;
	i = 0;
	while (pos[i])
	{
		if (pos[i] == cast)
			return (&pos[i]);
		i++;
	}
	if (cast == pos[i])
		return (&pos[i]);
	return (0);
}
