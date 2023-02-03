/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_error_message.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzblah <mehdi.zblah@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 14:05:42 by mzblah            #+#    #+#             */
/*   Updated: 2021/05/29 15:47:28 by mzblah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_exit_inutile(t_c3d *cub)
{
	ft_exit_cub3d(cub, 0);
	return (0);
}

int	ft_keep_reading_gnl(int fd, char **s)
{
	int		gnl;
	char	*str;

	if (s)
		free(*s);
	while (a(&gnl, get_next_line(fd, &str), 4, 0))
		free(str);
	free(str);
	close(fd);
	return (gnl);
}

int	ft_error_message(int state, int fd, int gnl)
{
	char	*str;

	if (a(&fd, open(ERR_FILE_PATH, O_RDONLY), 1, -1))
		return (-1);
	while (a(&gnl, get_next_line(fd, &str), 9, 0))
	{
		if (gnl == -1)
			return (-1);
		if (ft_atoi(str) == state)
		{
			ft_putstr_fd(&str[12], 1);
			write(1, "\n", 1);
			free(str);
			return (ft_keep_reading_gnl(fd, 0));
		}
		free(str);
	}
	ft_putstr_fd("Code erreur inconnu\n", 1);
	free(str);
	return (0);
}
