/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 11:23:59 by knajmech          #+#    #+#             */
/*   Updated: 2025/10/10 17:26:29 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	first_pos(char const *s1, char const *set)
{
	long int	count_set;
	long int	count_str;

	count_str = 0;
	while (s1[count_str])
	{
		count_set = 0;
		while (set[count_set])
		{
			if (set[count_set] == s1[count_str])
				break ;
			count_set++;
		}
		if (count_set == (long int)ft_strlen(set))
			return (count_str);
		count_str++;
	}
	return (count_str);
}

static int	last_pos(char const *s1, char const *set)
{
	long int	end;
	long int	count_set;

	end = ft_strlen(s1) - 1;
	while (end >= 0)
	{
		count_set = 0;
		while (set[count_set])
		{
			if (set[count_set] == s1[end])
				break ;
			count_set++;
		}
		if (count_set == (long int)ft_strlen(set))
			return (end);
		end--;
	}
	return (-1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*ptr;

	if (!s1 || !set)
		return (0);
	start = first_pos(s1, set);
	end = last_pos(s1, set);
	if (end < start)
		return (ft_strdup(""));
	ptr = ft_substr(s1, start, end - start + 1);
	if (!ptr)
		return (0);
	return (ptr);
}
