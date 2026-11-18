/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastalze <bastalze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 12:44:17 by bastalze          #+#    #+#             */
/*   Updated: 2026/11/18 17:25:26 by bastalze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_str_i(const char *s, int c)
{
	unsigned char	find;
	size_t			strlen;

	strlen = ft_strlen(s);
	find = (unsigned char) c;
	while (strlen + 1 > 0)
	{
		if (*s == find)
			return (strlen);
		s++;
		strlen--;
	}
	return (0);
}
