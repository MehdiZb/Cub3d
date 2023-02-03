/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_parse_map_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzblah <mehdi.zblah@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 17:02:13 by mzblah            #+#    #+#             */
/*   Updated: 2021/04/10 19:07:57 by mzblah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static char	*ft_map_str_adjust(t_l_str *map, size_t max_str_size)
{
	char	*str;
	size_t	cmpt;

	cmpt = ft_strlen(map->str);
	if (cmpt == max_str_size)
	{
		str = ft_strdup(map->str);
		if (!(str))
			return (NULL);
	}
	else if (!(ac((void **)&str, ft_strnew(max_str_size))))
		return (NULL);
	ft_strcpy(str, map->str);
	while (cmpt < max_str_size)
		str[cmpt++] = ' ';
	free(map->str);
	map->str = 0;
	return (str);
}

static int	ft_check_around(t_c3d *cub, size_t y, size_t x, size_t y_cpy)
{
	size_t	x_cpy;

	if (y == 0 || y + 1 == cub->map_height || x == 0 || x + 1 == cub->map_width)
		return (-115);
	while (y_cpy < y + 2)
	{
		x_cpy = x - 2;
		while (++x_cpy < x + 2)
		{
			if (cub->map[y_cpy][x_cpy] == ' ')
				return (-115);
		}
		y_cpy++;
	}
	if (!ft_chr_in_str("02345", cub->map[y][x]))
	{
		if (cub->pos_direction)
			return (-116);
		cub->pos_y = y;
		cub->pos_x = x;
		cub->pos_direction = cub->map[y][x];
	}
	return (0);
}

static int	ft_check_map(t_c3d *cub, int y)
{
	int		x;
	char	c;
	int		st;

	if (cub->map_height < 3 || cub->map_width < 3)
		return (-117);
	while (cub->map[++y])
	{
		x = 0;
		c = cub->map[y][x];
		while (c)
		{
			if (ft_chr_in_str(STR_SPR, c))
				cub->nb_spr++;
			if (!ft_chr_in_str(STR_VALID_BONUS, c))
				return (-114);
			else if (c != '1' && c != ' '
				&& (a(&st, ft_check_around(cub, y, x, (size_t)(y - 1)), 3, 0)))
				return (st);
			c = cub->map[y][++x];
		}
	}
	return (ft_stock_sprites(cub));
}

static int	ft_fill_cub_map(t_c3d *cub)
{
	size_t	cmpt;
	t_l_str	*tmp1;

	cub->map = (char **)malloc(sizeof(char *) * (cub->map_height + 1));
	if (!(cub->map))
		return (-121);
	ft_bzero(cub->map, sizeof(char *) * (cub->map_height + 1));
	cmpt = 0;
	tmp1 = cub->map_str;
	while (tmp1)
	{
		cub->map[cmpt++] = ft_map_str_adjust(tmp1, cub->map_width);
		if ((!(cub->map[cmpt - 1]))
			|| !cub->map[cmpt - 1])
			return (-113);
		cub->map_str = tmp1->next;
		free(tmp1);
		tmp1 = cub->map_str;
	}
	return (ft_check_map(cub, -1));
}

int	ft_parse_map(t_c3d *cub, int fd, char **f_str)
{
	int		ft_read;

	cub->map_str = (t_l_str *)malloc(sizeof(*cub->map_str));
	if (!(cub->map_str))
		return (-110);
	ft_bzero(cub->map_str, sizeof(*cub->map_str));
	cub->map_str->str = *f_str;
	cub->map_height++;
	cub->map_width = ft_strlen(*f_str);
	if (a(&ft_read, ft_read_map(cub, fd, &f_str), 2, 0))
		return (ft_read);
	if (*f_str && *f_str[0])
	{
		free(*f_str);
		*f_str = NULL;
		return (-118);
	}
	if (*f_str)
		free(*f_str);
	*f_str = NULL;
	return (ft_fill_cub_map(cub));
}
