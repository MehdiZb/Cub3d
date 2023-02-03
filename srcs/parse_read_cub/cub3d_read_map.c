/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_read_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzblah <mehdi.zblah@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 15:50:13 by mzblah            #+#    #+#             */
/*   Updated: 2021/05/30 16:50:23 by mzblah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	skip_spaces_comma(char *str, int *idx)
{
	while (str[*idx] == ' ')
		(*idx)++;
	if (str[*idx] == ',')
		(*idx)++;
	else
		return (1);
	while (str[*idx] == ' ')
		(*idx)++;
	return (0);
}

static void	ft_check_stock_sprites(t_c3d *cub, int y, int x, int idx)
{
	char	c;

	while (cub->map[++y])
	{
		x = 0;
		c = cub->map[y][x];
		while (c)
		{
			if (!ft_chr_in_str(STR_NO_SPR, c))
			{
				cub->spr_tab[idx]->x = (int)x;
				cub->spr_tab[idx]->y = (int)y;
				cub->spr_tab[idx++]->type = c;
			}
			c = cub->map[y][++x];
		}
	}
}

int	ft_stock_sprites(t_c3d *cub)
{
	int		idx;

	if (!cub->nb_spr)
		return (0);
	cub->nb_spr_final = cub->nb_spr;
	cub->spr_tab = (t_spr **)ft_calloc(cub->nb_spr, sizeof(t_spr *));
	if (!(cub->spr_tab))
		return (-130);
	idx = 0;
	while (idx < cub->nb_spr)
	{
		cub->spr_tab[idx] = (t_spr *)ft_calloc(1, sizeof(t_spr));
		if (!(cub->spr_tab[idx++]))
			return (-130);
	}
	ft_check_stock_sprites(cub, -1, 0, 0);
	return (0);
}

int	ft_read_map(t_c3d *cub, int fd, char ***f_str)
{
	int		gnl;
	t_l_str	*tmp_map;

	tmp_map = cub->map_str;
	while (a(&gnl, get_next_line(fd, *f_str), 4, 0) || **f_str[0])
	{
		tmp_map->next = (t_l_str *)malloc(sizeof(*tmp_map->next));
		if (!(tmp_map->next))
			return (-111);
		ft_bzero(tmp_map->next, sizeof(*tmp_map->next));
		tmp_map = tmp_map->next;
		tmp_map->str = **f_str;
		cub->map_height++;
		if (ft_strlen(**f_str) > cub->map_width)
			cub->map_width = ft_strlen(**f_str);
		**f_str = 0;
	}
	if (gnl != 0)
		return (-104);
	return (0);
}
