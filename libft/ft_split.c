/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 14:42:43 by knajmech          #+#    #+#             */
/*   Updated: 2026/02/12 11:01:14 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_count(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return (count);
}

static int	word_len(const char *s, char delimitter)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] && s[i] != delimitter)
		i++;
	return (i);
}

static char	**freedom(char **list, int times)
{
	while (times >= 0)
	{
		free(list[times]);
		list[times] = 0;
		times--;
	}
	free(list);
	list = 0;
	return (0);
}

static char	**mallocing(char const *s, char **list, char c)
{
	int	i;
	int	k;

	k = 0;
	i = 0;
	if (!list)
		return (0);
	while (s[i])
	{
		if (s[i] != c)
		{
			list[k] = ft_substr(s, i, word_len(&s[i], c));
			if (!list[k])
				return (freedom(list, k));
			k++;
			while (s[i] != c && (s[i]))
				i++;
		}
		else
			i++;
	}
	list[k] = 0;
	return (list);
}

char	**ft_split(char const *s, char c)
{
	char	**list;
	int		count;

	if (!s)
		return (0);
	count = word_count(s, c);
	if (!count)
		return (NULL);
	list = malloc(sizeof(char *) * (count + 1));
	if (!list)
		return (NULL);
	list = mallocing(s, list, c);
	return (list);
}
/*
static int main(void)
{
	char const s[] = "one two  three  four  five six";
	char **result = ft_split(s, ' ');
	int i = 0;

	while (i < 7)
	{
		printf("%s \n", result[i]);
		i++;
	}
}*/
