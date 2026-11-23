/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceiling_colours.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastalze <bastalze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/16 12:52:45 by bastalze          #+#    #+#             */
/*   Updated: 2026/11/23 11:51:52 by bastalze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	char_into_int_colours(int z, char *colour, t_colours *rgb)
{
	if (z == 0)
		rgb->red = ft_atoi(colour);
	else if (z == 1)
		rgb->green = ft_atoi(colour);
	else if (z == 2)
		rgb->blue = ft_atoi(colour);
	if (rgb->red > 255 || rgb->green > 255 || rgb->blue > 255)
		return(error("Invalid RGB value - higher than 255", false), 1);
	else
	 	return (0);
}

int	parse_rgb_number(int *i, char *colour, char *line)
{
	int	j;
	
	j = 0;
	while (j < 3 && line[*i] != ',' && line[*i] != '\n')
	{
		if (ft_isdigit(line[*i]))
			colour[j] = line[*i];
		else
			return (error("Wall or ceiling colours aren't positive numbers", false),
				1);
		(*i)++;
		j++;
	}
	colour[j] = 0;
	return (0);
}

int	parse_rgb_block(int *i, char *line, t_colours *rgb)
{
	
	int		z;
	char	colour[4];
	
	z = 0;
	while (line[*i] != ' ' && line[*i] != '\n' && line[*i])
	{
		if (parse_rgb_number(i, colour, line))
			return (1);
		if (char_into_int_colours(z, colour, rgb))
			return (1);
		z++;
		if (z >= 3)
			break ;
		if (line[*i] != ',')
			return (error("Wall or ceiling invalid input", false), 1);
		(*i)++;
	}
	return (0);
}

int	get_colour(t_storage *dat, char *line, int *elements, bool floor)
{
	int 		i;
	t_colours	rgb;
	
	i = 2;
	ft_bzero(&rgb, sizeof(t_colours));
	while (line[i] == ' ')
		i++;
	if (parse_rgb_block(&i, line, &rgb))
		return (1);
	while (line[i] == ' ')
		i++;
	if (line[i] == '\n')
	{
		if (rgb_to_int(dat, &rgb, floor))
			return (1);
		(*elements)++;
		return (0);
	}
	else
		return (error("Wall or ceiling line contains unexpected"
			" information", false), 1);
}
