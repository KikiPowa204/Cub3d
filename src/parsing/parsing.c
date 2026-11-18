/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastalze <bastalze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/13 12:48:19 by bastalze          #+#    #+#             */
/*   Updated: 2026/11/18 17:22:12 by bastalze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	store_texture_paths(t_compass dir, char **texture_paths, char *line, int *elements)
{
	int	i;
	int	j;
	size_t	len;

	i = 3;
	while(line[i] == ' ')
		i++;
	len = ft_strlen(&line[i]);
	if (texture_paths[dir] != NULL)
		return (error("Multiple listing of same texture", false), 1);
	texture_paths[dir] = malloc(len);
	j = 0;
	while(line[i] != ' ' && line[i])
	{
		texture_paths[dir][j] = line[i];
		j++;
		i++;
	}
	while(line[i] == ' ')
		i++;
	if (line[i] == '\n')
		return ((*elements)++, texture_paths[dir][j] = 0, 0);
	else
		return (error("Texture path not continuous", false), 1);
}

int	wfc(t_storage *dat, char **texture_paths, char *line, int *elements)
{
	if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
	{
		if (store_texture_paths(NO, texture_paths, line, elements))
			return (1);
	}
	else if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
	{
		if (store_texture_paths(SO, texture_paths, line, elements))
			return (1);
	}
	else if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
	{
		if (store_texture_paths(EA, texture_paths, line, elements))
			return (1);
	}
	else if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
	{
		if (store_texture_paths(WE, texture_paths, line, elements))
			return (1);
	}
	else if (line[0] == 'F' && line[1] == ' ')
	{
		if (get_colour(dat, line, elements, true))
			return (1);
	}
	else if (line[0] == 'C' && line[1] == ' ')
	{
		if (get_colour(dat, line, elements, false))
			return (1);
	}
	else if (line[0] != '\n')
		return (2);
	return (0);
}

int	parse_through(t_storage *dat, char **texture_paths, int fd, int map_fd)
{
	char	*line;
	int		elements;
	int		check;
	size_t	lines;
	
	lines = 0;
	errno = 0;
	elements = 0;
	while(elements < 7)
	{
		line = get_next_line(fd);
		if (errno != 0)
			return (error("Read failed", true), free(line), 1);
		if (!line)
			return (error("Description file has missing elements", false),
				free(line), 1);
		lines++;
		check = wfc(dat, texture_paths, line, &elements);
		if (check == 1)
			return (free(line), 1);
		if (check == 2)
			return (error("Invalid description file content", false),
				free(line), 1);
		free(line);
	}
	if (map_mode(dat, lines, fd, map_fd))
		return (1);
	return (0);
}

int	parse_description_file(char *path, t_storage *dat, char **texture_paths)
{
	int	fd;
	int	map_fd;

	ft_bzero(texture_paths, sizeof(char *) * 4);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (error("Description file could not be opened", true), 1);
	map_fd = open(path, O_RDONLY);
	if (map_fd == -1)
		return (error("Description file could not be opened", true), 1);
	if (parse_through(dat, texture_paths, fd, map_fd))
		return (1);
	return (0);
}