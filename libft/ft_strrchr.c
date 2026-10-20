/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 12:11:55 by knajmech          #+#    #+#             */
/*   Updated: 2025/10/21 09:07:26 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	size_t	counter;
	char	cast;

	cast = (char) c;
	str = (char *) s;
	counter = ft_strlen(str);
	while (s[counter] != cast)
	{
		if (str[counter] == cast)
			return (&str[counter]);
		else if (counter == 0)
			break ;
		counter--;
	}
	if (str[counter] == cast)
		return (&str[counter]);
	return (0);
}
