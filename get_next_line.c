/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thloyan <thloyan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 13:00:08 by thloyan           #+#    #+#             */
/*   Updated: 2022/12/02 18:44:37 by thloyan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	read_and_stash(t_list **lst, int fd)
{
	char	*buffer;
	int		readed;

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

size_t	compute_line_len(t_list *lst)
{
	size_t		len;
	size_t		i;

	len = 0;
	while (lst)
	{
		i = 0;
		while (lst->content[i] != 0 && lst->content[i] != '\n')
			i++;
		len = len + i;
		if (lst->content[i] == '\n' && len++)
			break ;
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
	if (!ft_strlen(*line))
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
	static t_list	*lst = NULL;
	char			*line;

	line = NULL;
	if (read(fd, 0, 0) == -1 || BUFFER_SIZE <= 0)
		return (ft_lstclear(&lst, &free), NULL);
	if (read_and_stash(&lst, fd) == -1)
		return (ft_lstclear(&lst, &free), NULL);
	line = malloc((compute_line_len(lst) + 1) * sizeof(*line));
	if (!line)
		return (ft_lstclear(&lst, &free), NULL);
	create_line(lst, &line);
	update_stash(&lst);
	return (line);
}
