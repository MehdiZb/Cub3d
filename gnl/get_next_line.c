/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzblah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 17:49:15 by mzblah            #+#    #+#             */
/*   Updated: 2019/12/02 17:51:34 by mzblah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	z(int *a, int b, int c, int d)
{
	*a = b;
	if (c == 0)
		return (0);
	if (c == 9)
		return (*a);
	if (c == 1)
		return (*a == d);
	if (c == 2)
		return (*a != d);
	if (c == 3)
		return (*a < d);
	if (c == 4)
		return (*a > d);
	return (0);
}

char	*zz(void **a, void *b)
{
	*a = b;
	return (*a);
}

int	w(int c, int a, int b)
{
	if (c)
		return (a);
	return (b);
}

int	ft_read_and_stock(t_gnl_fd *agf, char **line)
{
	int		ret;
	int		read_ret;

	read_ret = 1;
	if (z(&ret, ft_gnl_strjoin(line, agf->rest), 1, -1))
		return (-1);
	if (ret != -2 && ft_strcpy(agf->rest, agf->rest + ret))
		return (1);
	else if (ret == -2)
		agf->rest[0] = 0;
	while (ret == -2 && read_ret > 0)
	{
		ft_bzero((void *)agf->rest, BUFFER_SIZE + 1);
		if (z(&read_ret, read(agf->fd, agf->rest, BUFFER_SIZE), 1, -1))
			return (-1);
		if (z(&ret, ft_gnl_strjoin(line, agf->rest), 1, -1))
			return (-1);
	}
	if (read_ret)
		ft_strcpy(agf->rest, agf->rest + ret);
	else
		agf->rest[0] = 0;
	return (w((read_ret), 1, 0));
}

int	get_next_line(int fd, char **line)
{
	static t_gnl_fd		*first = NULL;
	t_gnl_fd			*agf;
	char				*ret_line;
	int					ft_return;

	if (!line || BUFFER_SIZE <= 0)
		return (-1);
	if (!zz((void **)&agf, ft_xetter_gnl_fd(fd, &first)))
		return (-1);
	if (!(agf->rest))
	{
		if (!zz((void **)&agf->rest,
				(char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
			return (-1);
		ft_bzero((void *)agf->rest, (BUFFER_SIZE + 1));
	}
	ret_line = 0;
	ft_return = ft_read_and_stock(agf, &ret_line);
	if (ft_return >= 0)
		*line = ret_line;
	if (ft_return <= 0)
		ft_del_gnl_fd(fd, &first);
	if (ft_return == -1 && ret_line)
		free(ret_line);
	return (ft_return);
}
