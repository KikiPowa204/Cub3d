/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_mode.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastalze <bastalze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/16 17:23:04 by bastalze          #+#    #+#             */
/*   Updated: 2026/11/23 17:09:40 by bastalze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <limits.h>

int	check_size(size_t lines, int fd, size_t start_map, t_storage *dat)
{
	char	*line;
	int	curr_len;
	
	errno = 0;
	while (42)
	{
		line = get_next_line(fd);
		if (errno != 0)
			return (error("Read failed", true), free(line), 1);
		if (!line)
			break ;
		curr_len = ft_strlen(line);
		if (curr_len != 0 && line[curr_len - 1] == '\n')
			curr_len--;
		if (dat->img->max_w < curr_len)
			dat->img->max_w = curr_len;
		lines++;
		if ((lines - start_map) * dat->img->max_w > INT_MAX)
			return (error("Map is too big (more than INT_MAX tiles)",
				false), free(line), 1);
		free(line);
	}
	dat->img->max_h = lines - start_map + 1;
	return (0);
}

void	copy_line(char **map_pos, char *line, int width)
{
	int	line_len;
	int	rest;
	
	line_len = ft_strlen(line);
	if (line_len > 0 && line[line_len - 1] == '\n')
		line_len--;
	ft_memcpy(*map_pos, line, line_len);
	rest = width - line_len;
	ft_memset(*map_pos + line_len, ' ', rest);
	*map_pos += width;
}

int	copy_map(t_storage *dat, int map_fd, size_t	start_map)
{
	size_t	lines;
	char	*line;
	char	*map_pos;
	
	errno = 0;
	lines = 0;
	map_pos = dat->map;
	while (42)
	{
		line = get_next_line(map_fd);
		//printf("Line: %s.\nMap:%s.\n", line, dat->map);
		if (errno != 0)
			return (error("Read failed", true), free(line), 1);
		if (!line)
			break ;
		lines++;
		if (lines <= start_map)
			continue ;
		if (line[0] == '\n')
			return (error("Empty line in map", false), 
				free(line), 1);
		//if (lines > start_map)
		copy_line(&map_pos, line, dat->img->max_w);
		free(line);
	}
	*map_pos = 0;
	return (0);
}

int	map_mode(t_storage *dat, size_t lines, int fd, int map_fd)
{
	size_t	start_map;

	dat->img->max_h = 0;
	start_map = lines;
	if (check_size(lines, fd, start_map, dat))
		return (1);
	dat->map = malloc(dat->img->max_w * dat->img->max_h + 1);
	if (!dat->map)
		return (error("Mallocation of map failed", true), 1);
	if (copy_map(dat, map_fd, start_map))
		return (free(dat->map), 1);
	if (check_map(dat))
		return (free(dat->map), 1);
	return (0);
}
