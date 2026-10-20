/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 17:44:56 by knajmech          #+#    #+#             */
/*   Updated: 2025/11/11 08:08:54 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	how_long(size_t num)
{
	int	div;

	if (!num)
		return (0);
	div = 0;
	while (num > 0)
	{
		num /= 16;
		div++;
	}
	return (div);
}

static void	recurse(size_t num, char *result, size_t len)
{
	const char	*dic;

	dic = "0123456789abcdef";
	if (num < 16)
	{
		result[len] = dic[num % 16];
		return ;
	}
	recurse(num / 16, result, len - 1);
	result[len] = dic[num % 16];
}

char	*ft_putnbr_base(long int nbr, char spec)
{
	size_t			len;
	char			*result;

	len = how_long(nbr);
	if (spec == 'p')
		len += 2;
	result = ft_calloc(len + 1, sizeof(char));
	recurse(nbr, result, len - 1);
	if (spec == 'p')
	{
		result[0] = '0';
		result[1] = 'x';
	}
	return (result);
}
/*int	main(void)
{
	char base[] = "01";
	int num = -21;

	ft_putnbr_base(num, base);
}*/
