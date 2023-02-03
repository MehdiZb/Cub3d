/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzblah <mehdi.zblah@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 21:49:22 by mzblah            #+#    #+#             */
/*   Updated: 2021/04/14 21:50:51 by mzblah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <sys/time.h>

void	ft_draw_weapon(t_c3d *cub, t_hud *hud, int x, int y)
{
	double	x_i;
	double	y_i;
	double	xo;
	double	yo;

	if (!hud->item_select || hud->items[hud->item_select - 1] == 0)
		return ;
	x_i = (double)hud->weapons_tex[W_SNIPE + hud->firing]->x / cub->res_width;
	y_i = (double)hud->weapons_tex[W_SNIPE + hud->firing]->y / cub->res_height;
	xo = x_i * 499;
	while (++x < cub->res_width)
	{
		yo = y_i * 298;
		y = 299;
		while (++y < cub->res_height)
		{
			(yo += y_i);
			if (yo && *hud->weapons_tex[W_SNIPE + hud->firing]
				->img_tab[(int)xo][(int)yo] != 0xFF000000)
				*cub->img[cub->idx_img]->img_tab[x][y] = *hud->weapons_tex
				[W_SNIPE + hud->firing]->img_tab[(int)xo][(int)yo];
		}
		xo += x_i;
	}
}

void	ft_shot_sprite(t_c3d *cub, t_ray *s_ray)
{
	if (ft_chr_in_str("24", cub->map[(int)s_ray->posy][(int)s_ray->posx]))
		return (ft_delete_sprite(cub, (int)s_ray->posx, (int)s_ray->posy));
	s_ray->camerax = 2 * cub->res_width / 2 / (double)cub->res_width - 1;
	s_ray->raydirx = s_ray->dirx + s_ray->planex * s_ray->camerax;
	s_ray->raydiry = s_ray->diry + s_ray->planey * s_ray->camerax;
	init_delta(s_ray, (s_ray->raydirx * s_ray->raydirx),
		(s_ray->raydiry * s_ray->raydiry));
	s_ray->hit = 0;
	while (s_ray->hit == 0)
	{
		if (s_ray->sidedistx < s_ray->sidedisty && !a(&s_ray->side, 0, 9, 0))
			s_ray->mapx += s_ray->stepx;
		if (s_ray->sidedistx < s_ray->sidedisty)
			s_ray->sidedistx += s_ray->deltadistx;
		else if (s_ray->sidedistx >= s_ray->sidedisty
			&& a(&s_ray->side, 1, 9, 0))
			s_ray->mapy += s_ray->stepy;
		if (s_ray->sidedistx >= s_ray->sidedisty && s_ray->side == 1)
			s_ray->sidedisty += s_ray->deltadisty;
		if (ft_chr_in_str("124", cub->map[s_ray->mapy][s_ray->mapx]))
			s_ray->hit = 1;
	}
	if (cub->map[s_ray->mapy][s_ray->mapx] != '1')
		ft_delete_sprite(cub, s_ray->mapx, s_ray->mapy);
}

void	ft_fire(t_c3d *cub, t_hud *hud)
{
	struct timeval	time;

	if (!hud->item_select || !hud->items[hud->item_select - 1])
		return ;
	if (!hud->ms_shoot_start)
	{
		hud->firing = 1;
		gettimeofday(&time, NULL);
		hud->ms_shoot_start = time.tv_usec + time.tv_sec * 1000000;
		ft_shot_sprite(cub, cub->s_ray);
	}
	gettimeofday(&time, NULL);
	if (time.tv_usec + time.tv_sec * 1000000 - hud->ms_shoot_start > 200000)
		hud->firing = 0;
}
