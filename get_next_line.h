/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thloyan <thloyan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 12:58:16 by thloyan           #+#    #+#             */
/*   Updated: 2022/12/02 20:39:10 by thloyan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

# include <limits.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list {
	char			*content;
	struct s_list	*next;
}	t_list;

char	*get_next_line(int fd);
int		read_and_stash(t_list **lst, int fd);
size_t	compute_line_len(t_list *lst);
void	create_line(t_list	*lst, char **line);
void	update_stash(t_list **lst);
void	ft_lstclear(t_list **lst, void (*del)(void *));
t_list	*ft_lstnew_gnl(t_list **lst, char *buffer);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);

#endif