/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastalze <bastalze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/13 13:02:50 by bastalze          #+#    #+#             */
/*   Updated: 2026/11/13 13:11:38 by bastalze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include <stddef.h>

void	error(const char *msg, bool perr)
{
	size_t	len;
	
	len = ft_strlen(msg);
	write(2, "Error\n", 6);
	if (perr == false)
	{
		write(2, msg, len);
		write(2, "\n", 1);
	}	
	else
		perror(msg);
}