/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 11:05:29 by knajmech          #+#    #+#             */
/*   Updated: 2025/11/05 16:22:01 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	how_long(long int num)
{
	int	div;

	if (!num)
		return (0);
	div = 0;
	while (num > 0)
	{
		num /= 10;
		div++;
	}
	return (div);
}

static void	check_neg(long int *new, int *power)
{
	power[0]++;
	*new *= -1;
}

static char	*check_rec(long int new, char *a_num, int power)
{
	if (power < 0)
		return (a_num);
	a_num[power] = (new % 10) + '0';
	new /= 10;
	power--;
	check_rec(new, a_num, power);
	return (a_num);
}

char	*ft_itoa(long int n)
{
	long int	new;
	char		*a_num;
	int			power;

	new = n;
	power = 0;
	if (!n)
		return (ft_strdup("0"));
	if (new < 0)
		check_neg(&new, &power);
	power += (how_long(new)-1);
	a_num = malloc(sizeof(char) * (power + 2));
	if (!a_num)
		return (0);
	a_num[power + 1] = '\0';
	a_num = check_rec(new, a_num, power);
	if (n < 0)
		a_num[0] = '-';
	return (a_num);
}

/*int	main(int argc, char **argv)
{
	if (argc < 2)
		return (0);
	int n = atoi(argv[1]);
	printf("%s", ft_itoa(n));
}*/
