/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastalze <bastalze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/13 12:48:19 by bastalze          #+#    #+#             */
/*   Updated: 2026/11/24 12:15:17 by bastalze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

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
	if (!texture_paths[dir])
		return (error("Malloc for texture_path failed", true), 1);
	j = 0;
	while(line[i] != ' ' && line[i] != '\n' && line[i])
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
	return (error("Invalid input in description file", false), 1);
}

int	handle_line(t_storage *dat, char **texture_paths, char *line, int *elements)
{
	//printf("Amount of elements:%d Line:%s\n", *elements, line);
	if (line[0] == '\n')
		return (0);
	if (ft_strlen(line) <= 3)
		return (error("Invalid description file content", false), 1);
	return (wfc(dat, texture_paths, line, elements));
}

int	parse_through(t_storage *dat, char **texture_paths, int fd, int map_fd)
{
	char	*line;
	int		elements;
	size_t	lines;
	
	lines = 0;
	elements = 0;
	while(42)
	{
		errno = 0;
		line = get_next_line(fd);
		if (errno != 0)
			return (error("Read failed", true), free(line), 1);
		if (!line)
			return (error("Description file has missing elements", false), 1);
		if (line[0] != '\n' && elements == 6)
			break ;
		lines++;
		if (handle_line(dat, texture_paths, line, &elements))
			return (free(line), 1);
		free(line);
	}
	if (map_mode(dat, lines, fd, map_fd))
		return (1);
	return (0);
}

int	check_path_ending(char *path)
{
	size_t len;

	len = ft_strlen(path);
	if (len < 4)
		return (error("Description file doesn't end in '.cub'", false), 1);
	path += (len - 4);
	if (ft_strncmp(path, ".cub", 4))
		return (error("Description file doesn't end in '.cub'", false), 1);
	return (0);
}

int	parse_description_file(char *path, t_storage *dat, char **texture_paths)
{
	int	fd;
	int	map_fd;

	if (check_path_ending(path))
		return (1);
	ft_bzero(texture_paths, sizeof(char *) * 4);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (error("Description file could not be opened", true), 1);
	map_fd = open(path, O_RDONLY);
	if (map_fd == -1)
		return (error("Description file could not be opened", true),
			close(fd), 1);
	if (parse_through(dat, texture_paths, fd, map_fd))
		return (close(fd), close(map_fd), 1);
	return (close(fd), close(map_fd), 0);
}
