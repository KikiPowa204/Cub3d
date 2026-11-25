/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 09:44:25 by knajmech          #+#    #+#             */
/*   Updated: 2026/11/25 10:31:44 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_resize(char *line, t_l *node, unsigned int term)
{
	char	*new;
	int		i;

	new = malloc((node->l_index + node->bytes_read + 1) * sizeof(char));
	if (!new)
		return (free(new), free(line), NULL);
	i = 0;
	while (i <= node->l_index)
	{
		new[i] = line[i];
		i++;
	}
	if (term)
		new[i] = '\0';
	free(line);
	line = new;
	return (line);
}

char	*last_run(t_l *node, char *line)
{
	if (node->l_index)
		line = ft_resize(line, node, 0);
	if (!line)
		return (NULL);
	while (node->b_index < node->bytes_read)
	{
		line[node->l_index] = node->buff[node->b_index];
		if (line[node->l_index] == '\n')
		{
			if (node->b_index + 1 == node->bytes_read)
				node->start = 0;
			return (node->b_index++, line[node->l_index + 1] = '\0', line);
		}
		node->b_index++;
		node->l_index++;
	}
	line[node->l_index] = '\0';
	node->start = 0;
	return (line);
}

void	read_buff(int fd, t_l *node)
{
	if (!node->start)
	{
		node->bytes_read = read(fd, node->buff, BUFFER_SIZE);
		if (node->bytes_read <= 0)
		{
			node->start = 0;
			return ;
		}
		node->start = 1;
		return ;
	}
	else if (node->start == 1)
	{
		node->bytes_read = read(fd, node->buff, BUFFER_SIZE);
		if (node->bytes_read == 0)
			node->start = 2;
		else if (node->bytes_read < 0)
			node->start = 0;
		return ;
	}
}

char	*get_nl(int fd, char *line, t_l *node)
{
	while (node->bytes_read > 0 || !node->start)
	{
		if (!node->b_index)
			read_buff(fd, node);
		if (!node->start)
			return (free(line), NULL);
		if (node->start == 2)
			return (last_run(node, line));
		line[node->l_index] = node->buff[node->b_index];
		if (line[node->l_index] == '\n')
		{
			line = ft_resize(line, node, 1);
			return (node->b_index++, line);
		}
		node->b_index++;
		node->l_index++;
		if (node->b_index >= node->bytes_read)
		{
			line = ft_resize(line, node, 0);
			if (!line)
				return (NULL);
			node->b_index = 0;
		}
	}
	return (ft_resize(line, node, 1));
}

char	*get_next_line(int fd)
{
	static t_l	node[1024];
	char		*line;

	line = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!line || fd < 0)
		return (free(line), NULL);
	line[BUFFER_SIZE] = '\0';
	if (node->start == 2)
		return (last_run(&node[fd], line));
	line = get_nl(fd, line, &node[fd]);
	if (node[fd].b_index >= node[fd].bytes_read)
		node[fd].b_index = 0;
	node[fd].l_index = 0;
	if (node[fd].bytes_read == 0 && BUFFER_SIZE == 1)
		node[fd].start = 0;
	if (!line)
		return (NULL);
	if (node[fd].bytes_read == 0 && line[0] == '\0')
		return (free(line), NULL);
	return (line);
}
/*
#include <fcntl.h>
#include <stdio.h>
int main(int argc, char **argv)
{
	int fd = open(argv[1], O_RDONLY);
	int run;
	char *result = "default";
	
	argc = 0;
	run = 0;
	while ((result = get_next_line(fd)))
	{
		printf("line: %s", result);
		run++;
		free(result);
	}
	//close(fd);
}*/
