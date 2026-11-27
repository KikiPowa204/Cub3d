/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_mode.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastalze <bastalze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/16 17:23:04 by bastalze          #+#    #+#             */
/*   Updated: 2026/11/27 17:47:23 by bastalze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <limits.h>
#include <stdbool.h>

int	check_size(size_t lines, int fd, size_t start_map, t_storage *dat)
{
	char	*line;
	int		curr_len;

	errno = 0;
	while (42)
	{
		line = get_next_line(fd);
		if (errno != 0)
			return (ft_error("Read failed", true), free(line), 1);
		if (!line)
			break ;
		curr_len = line_len(line);
		if (dat->max_w < curr_len)
			dat->max_w = curr_len;
		lines++;
		if ((lines - start_map) * dat->max_w > INT_MAX)
			return (ft_error("Map is too big (more than INT_MAX tiles)",
					false), free(line), 1);
		free(line);
	}
	dat->max_h = lines - start_map + 1;
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

int	skip_ahead(int map_fd, size_t start_map)
{
	size_t	lines;
	char	*line;

	errno = 0;
	lines = 0;
	while (lines++ <= start_map - 1)
	{
		line = get_next_line(map_fd);
		if (errno != 0)
			return (ft_error("Read failed", true), free(line), 1);
		free(line);
	}
	return (0);
}

int	copy_map(t_storage *dat, int map_fd, size_t	start_map)
{
	char	*line;
	char	*map_pos;
	bool	nl;

	errno = 0;
	nl = false;
	map_pos = dat->map;
	if (skip_ahead(map_fd, start_map))
		return (1);
	line = get_next_line(map_fd);
	while (line)
	{
		if (line[0] == '\n')
			nl = true;
		if (line[0] != '\n' && nl)
			return (ft_error("Empty line in map", false), free(line), 1);
		if (!nl)
			copy_line(&map_pos, line, dat->max_w);
		free(line);
		line = get_next_line(map_fd);
		if (!line && errno)
			return (ft_error("Read failed", true), free(line), 1);
	}
	return (free(line), *map_pos = 0, 0);
}

int	map_mode(t_storage *dat, size_t lines, int fd, int map_fd)
{
	size_t	start_map;

	dat->max_h = 0;
	start_map = lines;
	if (check_size(lines, fd, start_map, dat))
		return (1);
	if (dat->max_h > MINI_VIEW)
		dat->mini.mini_h = MINI_VIEW;
	else
		dat->mini.mini_h = dat->max_h;
	if (dat->max_w > MINI_VIEW)
		dat->mini.mini_w = MINI_VIEW;
	else
		dat->mini.mini_w = dat->max_w;
	dat->map = malloc(dat->max_w * dat->max_h + 1);
	if (!dat->map)
		return (ft_error("Mallocation of map failed", true), 1);
	if (copy_map(dat, map_fd, start_map))
		return (1);
	if (check_map(dat))
		return (1);
	return (0);
}
