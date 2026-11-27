/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line_len.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastalze <bastalze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/13 12:48:19 by bastalze          #+#    #+#             */
/*   Updated: 2026/11/27 17:44:27 by bastalze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	line_len(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (len != 0 && line[len - 1] == '\n')
			len--;
	return (len);
}