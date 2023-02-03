/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_raycasting_sprite.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzblah <mehdi.zblah@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 20:01:23 by mzblah            #+#    #+#             */
/*   Updated: 2021/03/22 15:36:12 by mzblah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	sort_swipe_sprites(t_c3d *cub)
{
	int		bool_mv;
	int		idx;
	t_spr	*tmp;

	idx = 0;
	bool_mv = 0;
	while (idx < cub->nb_spr - 1)
	{
		if (cub->spr_tab[idx]->dist < cub->spr_tab[idx + 1]->dist)
		{
			tmp = cub->spr_tab[idx];
			cub->spr_tab[idx] = cub->spr_tab[idx + 1];
			cub->spr_tab[idx + 1] = tmp;
			bool_mv = 1;
		}
		idx++;
	}
	if (bool_mv)
		sort_swipe_sprites(cub);
}

static void	ft_calc_sprit_dimensions(t_c3d *cub, t_spr *s, t_ray *s_r)
{
	s->pos_cam_x = s->x + 0.5 - s_r->posx;
	s->pos_cam_y = s->y + 0.5 - s_r->posy;
	s->transform_x = s_r->spr_inv_det
		* (s_r->diry * s->pos_cam_x - s_r->dirx * s->pos_cam_y);
	s->transform_y = s_r->spr_inv_det
		* (-s_r->planey * s->pos_cam_x + s_r->planex * s->pos_cam_y);
	s->spr_screen_x = (int)((cub->res_width / 2)
			* (1 + s->transform_x / s->transform_y));
	s->spr_height = abs((int)(cub->res_height / (s->transform_y)));
	s->draw_start_y = -s->spr_height / 2 + cub->res_height / 2;
	if (s->draw_start_y < 0)
		s->draw_start_y = 0;
	s->draw_end_y = s->spr_height / 2 + cub->res_height / 2;
	if (s->draw_end_y >= cub->res_height)
		s->draw_end_y = cub->res_height - 1;
	s->spr_width = abs((int)(cub->res_height / (s->transform_y)));
	s->draw_start_x = -s->spr_width / 2 + s->spr_screen_x;
	if (s->draw_start_x < 0)
		s->draw_start_x = 0;
	s->draw_end_x = s->spr_width / 2 + s->spr_screen_x;
	if (s->draw_end_x >= cub->res_width)
		s->draw_end_x = cub->res_width - 1;
}

static void	ft_while_draw_sprite(t_c3d *cub, t_spr *s, double *dist_buffer,
	int i)
{
	s->ix = s->draw_start_x - 1;
	while (++s->ix < s->draw_end_x)
	{
		s->tex_x = (int)(256 * (s->ix - (-s->spr_width / 2 + s->spr_screen_x))
				* cub->img_textures[i]->x / s->spr_width) / 256;
		if (s->transform_y > 0 && s->ix > 0 && s->ix < cub->res_width
			&& s->transform_y < dist_buffer[s->ix])
		{
			s->iy = s->draw_start_y - 1;
			while (++s->iy < s->draw_end_y)
			{
				s->tex_y = ((((s->iy) * 256
								- cub->res_height * 129 + s->spr_height * 128)
							* cub->img_textures[i]->y) / s->spr_height) / 256;
				if (s->tex_y < 0)
					s->tex_y = 0;
				if (s->tex_x < 0)
					s->tex_x = 0;
				if ((*cub->img_textures[i]->img_tab[s->tex_x][s->tex_y]
					& 0x00FFFFFF) != 0)
					*cub->img[cub->idx_img]->img_tab[s->ix][s->iy]
						= *cub->img_textures[i]->img_tab[s->tex_x][s->tex_y];
			}
		}
	}
}

void	ft_delete_sprite(t_c3d *cub, int x, int y)
{
	int	idx;

	idx = -1;
	while (++idx < cub->nb_spr)
	{		
		if (cub->spr_tab[idx]->x == x && cub->spr_tab[idx]->y == y)
		{
			cub->spr_tab[idx]->type = cub->spr_tab[cub->nb_spr - 1]->type;
			cub->spr_tab[idx]->x = cub->spr_tab[cub->nb_spr - 1]->x;
			cub->spr_tab[idx]->y = cub->spr_tab[cub->nb_spr - 1]->y;
		}
	}
	cub->nb_spr--;
	cub->map[y][x] = '0';
	return ;
}

void	ft_draw_sprite(t_c3d *cub, t_ray *s_r, double *dist_buffer)
{
	int		idx;
	t_spr	*s;

	idx = -1;
	while (++idx < cub->nb_spr)
		cub->spr_tab[idx]->dist
			= ((s_r->posx - (double)cub->spr_tab[idx]->x)
				* (s_r->posx - (double)cub->spr_tab[idx]->x)
				+ (s_r->posy - (double)cub->spr_tab[idx]->y)
				* (s_r->posy - (double)cub->spr_tab[idx]->y));
	sort_swipe_sprites(cub);
	s_r->spr_inv_det = 1.0
		/ (s_r->planex * s_r->diry - s_r->dirx * s_r->planey);
	idx = -1;
	while (++idx < cub->nb_spr)
	{
		s = cub->spr_tab[idx];
		ft_calc_sprit_dimensions(cub, s, s_r);
		ft_while_draw_sprite(cub, s, dist_buffer, s->type - 46);
	}
}
