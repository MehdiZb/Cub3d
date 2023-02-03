/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzblah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 17:50:23 by mzblah            #+#    #+#             */
/*   Updated: 2019/12/02 17:43:57 by mzblah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

/*
**	DEFINES
*/

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 128
# endif

/*
**	INCLUDES
*/

# include <stdlib.h>
# include <unistd.h>

/*
**	STRUCT
*/

typedef struct s_get_next_line_fd
{
	struct s_get_next_line_fd	*next;
	int							fd;
	char						*rest;
}					t_gnl_fd;

/*
**	PROTOTYPES
*/

void				ft_bzero(void *s, size_t n);
char				*ft_strcpy(char *dest, char *src);
int					ft_gnl_strjoin(char **s1, char *s2);
void				ft_del_gnl_fd(int fd, t_gnl_fd **first);
t_gnl_fd			*ft_xetter_gnl_fd(int fd, t_gnl_fd **first);

int					get_next_line(int fd, char **line);
int					z(int *a, int b, int c, int d);
char				*zz(void **a, void *b);
int					w(int c, int a, int b);

#endif
