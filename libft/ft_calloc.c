/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 10:26:42 by knajmech          #+#    #+#             */
/*   Updated: 2025/10/23 09:30:42 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*ptr;

	if (!nmemb || !size)
		return (malloc(0));
	if (nmemb && size > LLONG_MAX / nmemb)
		return (0);
	ptr = malloc(size * nmemb);
	if (!ptr || !nmemb)
		return (ptr);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}
