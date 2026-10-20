/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 11:20:09 by knajmech          #+#    #+#             */
/*   Updated: 2026/02/20 13:17:21 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	skip_space(const char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if ((input[i] >= 9 && input[i] <= 13) || input[i] == 32)
			i++;
		else
			return (i);
	}
	return (0);
}

static char	*just_hex_stuff(char *x, char spec, va_list *arg)
{
	int				i;
	long			temp;

	if (spec == 'p')
	{
		temp = va_arg(*arg, long int);
		if (!temp)
			return (ft_strdup("(nil)"));
		x = ft_putnbr_base(temp, spec);
	}
	else
	{
		temp = va_arg(*arg, unsigned int);
		if ((!temp) && (spec == 'x' || spec == 'X'))
			return (ft_itoa(0));
		x = ft_putnbr_base(temp, spec);
	}
	i = 0;
	while (x[i++])
		if (spec == 'X')
			x[i - 1] = ft_toupper(x[i - 1]);
	return (x);
}

static char	*redirect(char spec, va_list *arg)
{
	char	*x;

	x = 0;
	if (spec == 'd' || spec == 'i')
		return (ft_itoa(va_arg(*arg, int)));
	else if (spec == 'u')
		return (ft_itoa((unsigned int)va_arg(*arg, unsigned int)));
	else if (spec == 'x' || spec == 'X' || spec == 'p')
		x = just_hex_stuff(x, spec, arg);
	else if (spec == '%')
		x = ft_strdup("%");
	if (spec == 's')
	{
		x = ft_strdup(va_arg(*arg, char *));
		if (!x)
			return (ft_strdup("(null)"));
	}
	return (x);
}

static long int	parser(const char *str, long rv, long int *num, va_list *arg)
{
	char	*param;
	int		skipped_spaces;

	param = 0;
	skipped_spaces = skip_space(&str[rv + 1]) + 1;
	if (str[rv + skipped_spaces] == 'c')
		(*num) += ft_putchar_fd(va_arg(*arg, int), 1);
	else
	{
		param = redirect(str[rv + skipped_spaces], arg);
		*num += ft_strlen(param);
		ft_putstr_fd(param, 1);
		if (param)
			free(param);
	}
	return (rv += skipped_spaces + 1);
}

int	ft_printf(const char *str, ...)
{
	va_list		arg;
	long int	rv;
	long int	num;

	rv = 0;
	num = 0;
	va_start(arg, str);
	while (str[rv])
	{
		if (str[rv] == '%')
		{
			if (str[rv + 1] == '\0')
				return (va_end(arg), -1);
			rv = parser(str, rv, &num, &arg);
		}
		else
		{
			ft_putchar_fd(str[rv], 1);
			rv++;
			num++;
		}
	}
	return (va_end(arg), num);
}
