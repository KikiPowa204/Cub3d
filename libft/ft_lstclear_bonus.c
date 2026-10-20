/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 11:38:44 by knajmech          #+#    #+#             */
/*   Updated: 2026/02/10 10:16:08 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

void	ft_lstclear(t_stack **lst)
{
	t_stack	*address;
	t_stack	*head;
	int		start;

	if (!lst)
		return ;
	head = (*lst);
	start = 0;
	while ((*lst) != (head) || !(start))
	{
		start++;
		if (!(*lst))
			return ;
		address = *lst;
		if ((*lst)->next)
			*lst = (*lst)->next;
		else if (!(*lst)->next)
		{
			free(address);
			return ;
		}
		free(address);
		address = NULL;
	}
}
