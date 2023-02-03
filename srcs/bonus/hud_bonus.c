/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzblah <mehdi.zblah@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 15:48:42 by mzblah            #+#    #+#             */
/*   Updated: 2021/04/14 21:49:49 by mzblah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <sys/time.h>

static void	ft_draw_hotbar(t_hud *hud)
{
	int	i;
	int	x;
	int	y;
	int	start_y;

	start_y = hud->hud_tex[HP_FULL]->y;
	x = -1;
	while (++x < hud->hud_tex[MC_BAR]->x && a(&y, -1, 9, 0))
		while (++y < hud->hud_tex[MC_BAR]->y)
			if (*hud->hud_tex[MC_BAR]->img_tab[x][y] != 0xff000000)
				*hud->hud_img->img_tab[x][start_y + y]
					= *hud->hud_tex[MC_BAR]->img_tab[x][y];
	i = -1;
	while (++i < 9)
		if (hud->items[i] && a(&x, -1, 9, 0))
			while (++x < 63 && a(&y, -1, 9, 0))
				while (++y < 63)
					*hud->hud_img->img_tab[x + 12 + i * 80][start_y + 12 + y]
						= *hud->hud_tex[hud->items[i] + 1]->img_tab[x][y];
}

static void	ft_draw_hud(t_c3d *cub, t_hud *hud)
{
	int	h;
	int	i;
	int	x;
	int	y;

	hud->old_hp = cub->hp;
	i = -1;
	while (++i < 10)
	{
		h = HP_FULL;
		if ((i + 1) * 2 > cub->hp)
			h = t((i * 2 + 1 <= cub->hp), HP_HALF, HP_VOID);
		x = -1;
		while (++x < hud->hud_tex[h]->x && a(&y, -1, 9, 0))
			while (++y < hud->hud_tex[h]->y)
				if (*hud->hud_tex[h]->img_tab[x][y] != 0xff000000)
					*hud->hud_img->img_tab[x + (hud->hud_tex[h]->x * i)][y]
						= *hud->hud_tex[h]->img_tab[x][y];
	}
	ft_draw_hotbar(hud);
}

static int	ft_add_remove_life(t_c3d *cub)
{
	struct timeval	time;

	if (cub->map[(int)cub->s_ray->posy][(int)cub->s_ray->posx] == '4')
	{
		gettimeofday(&time, NULL);
		if (!cub->ms_life)
			if (cub->hp)
				cub->hp--;
		cub->ms_life += time.tv_usec + time.tv_sec * 1000000 - cub->ms_start;
		if (cub->ms_life > 250000)
		{
			cub->ms_life = 1;
			cub->hp--;
		}
		if (!cub->hp)
		{
			write(1, "MORT\n", 5);
			ft_exit_cub3d(cub, 0);
		}
	}
	if (cub->map[(int)cub->s_ray->posy][(int)cub->s_ray->posx] == '5')
		cub->hp = 20;
	if (cub->map[(int)cub->s_ray->posy][(int)cub->s_ray->posx] == '5')
		ft_delete_sprite(cub, (int)cub->s_ray->posx, (int)cub->s_ray->posy);
	return (0);
}

int	ft_special_case(t_c3d *cub)
{
	int	idx;

	if (cub->map[(int)cub->s_ray->posy][(int)cub->s_ray->posx] == '0')
		return (0);
	if (cub->map[(int)cub->s_ray->posy][(int)cub->s_ray->posx] == '4' ||
		cub->map[(int)cub->s_ray->posy][(int)cub->s_ray->posx] == '5')
		return (ft_add_remove_life(cub));
	cub->ms_life = 0;
	idx = 0;
	while (cub->hud->items[idx] && idx < 9)
		idx++;
	if (idx == 9)
		return (0);
	cub->hud->items[idx]
		= cub->map[(int)cub->s_ray->posy][(int)cub->s_ray->posx] - 48;
	ft_delete_sprite(cub, (int)cub->s_ray->posx, (int)cub->s_ray->posy);
	ft_draw_hud(cub, cub->hud);
	idx = -1;
	return (0);
}

int	ft_hud(t_c3d *cub)
{
	t_img	*hud_img;
	int		start_x;
	int		start_y;
	int		x;
	int		y;

	ft_special_case(cub);
	if (cub->hud->shoot_key || cub->hud->firing)
		ft_fire(cub, cub->hud);
	else if (cub->hud->shoot_key == 0)
		cub->hud->ms_shoot_start = 0;
	ft_draw_weapon(cub, cub->hud, 499, 299);
	if (cub->hud->old_hp != cub->hp)
		ft_draw_hud(cub, cub->hud);
	start_x = (cub->res_width - cub->hud->hud_tex[MC_BAR]->x) / 2;
	start_y = (cub->res_height - cub->hud->hud_tex[MC_BAR]->y * 1.5
			- cub->hud->hud_tex[HP_FULL]->y);
	x = -1;
	hud_img = cub->hud->hud_img;
	while (++x < hud_img->x && a(&y, -1, 9, 0))
		while (++y < hud_img->y)
			if (*hud_img->img_tab[x][y] != 0xff000000)
				*cub->img[cub->idx_img]->img_tab
				[start_x + x][start_y + y] = *hud_img->img_tab[x][y];
	return (0);
}
