/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 12:00:36 by knajmech          #+#    #+#             */
/*   Updated: 2026/02/11 07:11:21 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "libft.h"

// static void	*freedom(void *del_func, t_stack *add, void (*del)(void *))
// {
// 	del(del_func);
// 	if (add)
// 		ft_lstclear(&add, del);
// 	return (0);
// }

// t_stack	*ft_lstmap(t_stack *lst, void *(*f)(void *), void (*del)(void *))
// {
// 	t_stack	*new;
// 	t_stack	*add;
// 	void	*del_func;

// 	add = 0;
// 	if (!lst)
// 		return (0);
// 	del_func = f(lst->num);
// 	new = ft_lstnew(del_func);
// 	if (!new)
// 		return (freedom(del_func, add, del));
// 	add = new;
// 	lst = lst->next;
// 	while (lst)
// 	{
// 		del_func = f(lst->num);
// 		(new->next) = ft_lstnew(del_func);
// 		if (!(new->next))
// 			return (freedom(del_func, add, del));
// 		lst = lst->next;
// 		new = new->next;
// 	}
// 	return (add);
// }
/*
static void *dup_and_upper(void *str)
{
    char *s = ft_strdup((char *)str);
    for (int i = 0; s[i]; i++)
        if (s[i] >= 'a' && s[i] <= 'z')
            s[i] -= 32;
    return (s);
}

static int main(void)
{
    t_list *a = ft_lstnew(ft_strdup("one"));
    t_list *b = ft_lstnew(ft_strdup("two"));
    a->next = b;

    t_list *new_list = ft_lstmap(a, &dup_and_upper, free);

    printf("%s %s\n", new_list->content, "ONE");
    printf("%s %s", new_list->next->content, "TWO");

    ft_lstclear(&a, free);
    ft_lstclear(&new_list, free);
}*/
