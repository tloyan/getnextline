/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thloyan <thloyan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:18:05 by thloyan           #+#    #+#             */
/*   Updated: 2022/12/16 12:44:45 by thloyan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	read_and_stash(t_list **lst, int fd)
{
	char	*buffer;
	int		readed;

	if (*lst && ft_strchr((*lst)->content, '\n'))
		return (0);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(*buffer));
	if (!buffer)
		return (-1);
	buffer[0] = 0;
	readed = 1;
	while (readed && !ft_strchr(buffer, '\n'))
	{
		readed = read(fd, buffer, BUFFER_SIZE);
		if (readed == -1)
			return (free(buffer), -1);
		buffer[readed] = 0;
		if (ft_lstnew_gnl(&*lst, buffer) == NULL)
			return (free(buffer), -1);
	}
	return (free(buffer), 0);
}

int	ft_lstsize(t_list *lst)
{
	int	len;

	len = 0;
	while (lst)
	{
		len = len + 1;
		lst = lst->next;
	}
	return (len);
}

void	create_line(t_list	*lst, char **line)
{
	size_t		len;
	size_t		i;

	len = 0;
	while (lst)
	{
		i = 0;
		while (lst->content[i] != 0 && lst->content[i] != '\n')
			(*line)[len++] = lst->content[i++];
		if (lst->content[i] == '\n')
		{
			(*line)[len++] = lst->content[i++];
			break ;
		}
		lst = lst->next;
	}
	(*line)[len] = 0;
	if (len == 0)
	{
		free(*line);
		*line = NULL;
	}
}

void	update_stash(t_list **lst)
{
	char		*str;
	size_t		i;
	size_t		n;
	t_list		*tmp;

	while (*lst && !ft_strchr((*lst)->content, '\n'))
	{
		tmp = (*lst)->next;
		free((*lst)->content);
		free(*lst);
		*lst = tmp;
	}
	if (!*lst)
		return ;
	str = ft_strchr((*lst)->content, '\n') + 1;
	n = ft_strlen(str);
	i = 0;
	while (n--)
	{
		(*lst)->content[i] = str[i];
		i++;
	}
	(*lst)->content[i] = 0;
}

char	*get_next_line(int fd)
{
	static t_list	*lsts[FT_FD_MAX] = {};
	char			*line;

	line = NULL;
	if (fd > FT_FD_MAX || read(fd, 0, 0) == -1
		|| BUFFER_SIZE <= 0 || BUFFER_SIZE > (INT_MAX - 1))
		return (ft_lstclear(&lsts[fd], &free), NULL);
	if (read_and_stash(&lsts[fd], fd) == -1)
		return (ft_lstclear(&lsts[fd], &free), NULL);
	line = malloc(((ft_lstsize(lsts[fd]) * BUFFER_SIZE) + 1) * sizeof(*line));
	if (!line)
		return (ft_lstclear(&lsts[fd], &free), NULL);
	create_line(lsts[fd], &line);
	update_stash(&lsts[fd]);
	return (line);
}
