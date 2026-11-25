/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 09:53:06 by knajmech          #+#    #+#             */
/*   Updated: 2026/05/12 10:52:50 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

//# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct line_struct
{
	int				b_index;
	int				l_index;
	int				bytes_read;
	int				start;
	char			buff[BUFFER_SIZE];
}				t_l;

char		*get_next_line(int fd);
#endif
