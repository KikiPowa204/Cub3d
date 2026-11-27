/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastalze <bastalze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/13 12:48:19 by bastalze          #+#    #+#             */
/*   Updated: 2026/11/27 17:46:50 by bastalze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_line(t_storage *dat, char **texture_paths, char *line, int *elements)
{
	if (line[0] == '\n')
		return (0);
	if (ft_strlen(line) <= 3)
		return (ft_error("Invalid description file content", false), 1);
	return (wfc(dat, texture_paths, line, elements));
}

int	parse_through(t_storage *dat, char **texture_paths, int fd, int map_fd)
{
	char	*line;
	int		elements;
	size_t	lines;

	lines = 0;
	elements = 0;
	while (42)
	{
		errno = 0;
		line = get_next_line(fd);
		if (errno != 0)
			return (ft_error("Read failed", true), free(line), 1);
		if (!line)
			return (ft_error("Description file has missing element", false), 1);
		if (line[0] != '\n' && elements == 6)
			break ;
		lines++;
		if (handle_line(dat, texture_paths, line, &elements))
			return (free(line), 1);
		free(line);
	}
	dat->max_w = line_len(line);
	if (map_mode(dat, lines, fd, map_fd))
		return (free(line), 1);
	return (free(line), 0);
}

int	check_path_ending(char *path)
{
	size_t	len;

	len = ft_strlen(path);
	if (len < 4)
		return (ft_error("Description file doesn't end in '.cub'", false), 1);
	path += (len - 4);
	if (ft_strncmp(path, ".cub", 4))
		return (ft_error("Description file doesn't end in '.cub'", false), 1);
	return (0);
}

void	free_txt(char **texture_paths)
{
	free(texture_paths[NO]);
	texture_paths[NO] = NULL;
	free(texture_paths[SO]);
	texture_paths[SO] = NULL;
	free(texture_paths[EA]);
	texture_paths[EA] = NULL;
	free(texture_paths[WE]);
	texture_paths[WE] = NULL;
}

int	parse_description_file(char *path, t_storage *dat, char **texture_paths)
{
	int	fd;
	int	map_fd;

	if (check_path_ending(path))
		return (1);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (ft_error("Description file could not be opened", true), 1);
	map_fd = open(path, O_RDONLY);
	if (map_fd == -1)
		return (ft_error("Description file could not be opened", true),
			close(fd), 1);
	if (parse_through(dat, texture_paths, fd, map_fd))
		return (close(fd), close(map_fd), 1);
	return (close(fd), close(map_fd), 0);
}
