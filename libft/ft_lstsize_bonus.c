/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 10:42:47 by knajmech          #+#    #+#             */
/*   Updated: 2026/01/23 08:28:54 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_stack *lst)
{
	t_stack	*head;
	int		i;

	if (!lst)
		return (0);
	else if (lst->next == 0)
		return (1);
	head = lst;
	i = 1;
	while (lst->next != head)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
