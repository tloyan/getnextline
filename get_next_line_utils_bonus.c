/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thloyan <thloyan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:18:14 by thloyan           #+#    #+#             */
/*   Updated: 2022/12/03 02:44:01 by thloyan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	while (*lst)
	{
		tmp = (*lst)->next;
		if (del)
			del((*lst)->content);
		free(*lst);
		*lst = tmp;
	}
}

t_list	*ft_lstnew_gnl(t_list **lst, char *buffer)
{
	t_list	*begin;
	t_list	*new;
	char	*content;

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	content = ft_strdup(buffer);
	if (!content)
		return (free(new), NULL);
	new->content = (void *)content;
	new->next = NULL;
	if (!*lst)
		return (*lst = new);
	begin = *lst;
	while ((*lst)->next)
		*lst = (*lst)->next;
	(*lst)->next = new;
	*lst = begin;
	return (*lst);
}

char	*ft_strchr(const char *s, int c)
{
	unsigned long	i;

	if (c == 0)
		return ((char *)(s + ft_strlen(s)));
	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return ((char *)(s + i));
		i = i + 1;
	}
	return (NULL);
}

char	*ft_strdup(const char *s)
{
	char	*dst;
	int		i;

	dst = (char *)malloc((ft_strlen(s) + 1) * sizeof(*s));
	if (!dst)
		return (NULL);
	i = 0;
	while (*s)
		dst[i++] = *s++;
	dst[i] = 0;
	return (dst);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
