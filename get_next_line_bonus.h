/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thloyan <thloyan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:16:47 by thloyan           #+#    #+#             */
/*   Updated: 2022/12/02 18:44:40 by thloyan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

# ifndef FT_FD_MAX
#  define FT_FD_MAX 256
# endif

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