/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzblah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 11:08:21 by mzblah            #+#    #+#             */
/*   Updated: 2019/11/27 11:09:09 by mzblah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned long	i;

	i = 0;
	while (i < n)
		((char *)s)[i++] = 0;
}

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	ft_gnl_strjoin(char **s1, char *s2)
{
	char	*str;
	int		str_len;
	int		cmpt;
	int		cmpt_s2;

	str_len = 0;
	while (!z(&cmpt, 0, 9, 0) && (*s1) && (*s1)[str_len])
		str_len++;
	while (s2 && s2[cmpt] && s2[cmpt] != '\n')
		cmpt++;
	str_len += cmpt;
	if (!zz((void **)&str, malloc((sizeof(char) * (str_len + 1)))))
		return (-1);
	ft_bzero((void *)str, (str_len + 1));
	cmpt = -1;
	while ((*s1) && (*s1)[++cmpt])
		str[cmpt] = (*s1)[cmpt];
	cmpt_s2 = 0;
	cmpt += w((cmpt == -1), 1, 0);
	while (s2 && s2[cmpt_s2] && s2[cmpt_s2] != '\n')
		str[cmpt++] = s2[cmpt_s2++];
	if (*s1)
		free(*s1);
	*s1 = str;
	return (w((s2 && s2[cmpt_s2] == '\n'), cmpt_s2 + 1, -2));
}

void	ft_del_gnl_fd(int fd, t_gnl_fd **first)
{
	t_gnl_fd	*tmp_gnl_fd;
	t_gnl_fd	*free_gnl_fd;

	if (zz((void **)&tmp_gnl_fd, *first) && tmp_gnl_fd->fd == fd)
	{
		*first = tmp_gnl_fd->next;
		free(tmp_gnl_fd->rest);
		free(tmp_gnl_fd);
		return ;
	}
	while (tmp_gnl_fd->next && tmp_gnl_fd->next->fd != fd)
		tmp_gnl_fd = tmp_gnl_fd->next;
	free_gnl_fd = tmp_gnl_fd->next;
	tmp_gnl_fd->next = free_gnl_fd->next;
	free(tmp_gnl_fd->rest);
	free(free_gnl_fd);
}

t_gnl_fd	*ft_xetter_gnl_fd(int fd, t_gnl_fd **first)
{
	t_gnl_fd	*tmp_gnl_fd;
	t_gnl_fd	*new_gnl_fd;

	if (zz((void **)&tmp_gnl_fd, *first))
	{
		while (tmp_gnl_fd)
		{
			if (tmp_gnl_fd->fd == fd)
				return (tmp_gnl_fd);
			tmp_gnl_fd = tmp_gnl_fd->next;
		}
	}
	if (!zz((void **)&new_gnl_fd, (t_gnl_fd *)malloc(sizeof(t_gnl_fd))))
		return (0);
	ft_bzero((void *)new_gnl_fd, sizeof(t_gnl_fd));
	new_gnl_fd->fd = fd;
	if (!*first)
		*first = new_gnl_fd;
	else if (zz((void **)&tmp_gnl_fd, *first))
	{
		while (tmp_gnl_fd->next)
			tmp_gnl_fd = tmp_gnl_fd->next;
		tmp_gnl_fd->next = new_gnl_fd;
	}
	return (new_gnl_fd);
}
