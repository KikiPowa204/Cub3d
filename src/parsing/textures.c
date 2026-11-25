/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 14:29:06 by knajmech          #+#    #+#             */
/*   Updated: 2026/11/25 14:29:45 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	store_texture_paths(t_compass dir, char **texture_paths, char *line,
		int *elements)
{
	int		i;
	int		j;
	size_t	len;

	i = 3;
	while (line[i] == ' ')
		i++;
	len = ft_strlen(&line[i]);
	if (texture_paths[dir] != NULL)
		return (ft_error("Multiple listing of same texture", false), 1);
	texture_paths[dir] = malloc(len);
	if (!texture_paths[dir])
		return (ft_error("Malloc for texture_path failed", true), 1);
	j = 0;
	while (line[i] != ' ' && line[i] != '\n' && line[i])
		texture_paths[dir][j++] = line[i++];
	while (line[i] == ' ')
		i++;
	if (line[i] == '\n')
		return ((*elements)++, texture_paths[dir][j] = 0, 0);
	else
		return (ft_error("Texture path not continuous", false), 1);
}

int	wfc(t_storage *dat, char **texture_paths, char *line, int *elements)
{
	if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
		return (store_texture_paths(NO, texture_paths, line, elements));
	else if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
		return (store_texture_paths(SO, texture_paths, line, elements));
	else if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
		return (store_texture_paths(EA, texture_paths, line, elements));
	else if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
		return (store_texture_paths(WE, texture_paths, line, elements));
	else if (line[0] == 'F' && line[1] == ' ')
		return (get_colour(dat, line, elements, true));
	else if (line[0] == 'C' && line[1] == ' ')
		return (get_colour(dat, line, elements, false));
	return (ft_error("Invalid input in description file", false), 1);
}
