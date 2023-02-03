/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_texture_pixels.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzblah <mehdi.zblah@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 20:42:28 by mzblah            #+#    #+#             */
/*   Updated: 2021/03/22 15:39:42 by mzblah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	ft_calc_tex_x_y(t_c3d *cub, t_ray *s_r)
{
	if (s_r->side == 0)
		s_r->tex_idx = d((s_r->raydirx < 0), 1, 3);
	else if (s_r->side == 1)
		s_r->tex_idx = d((s_r->raydiry < 0), 2, 0);
	if (s_r->side == 0)
		s_r->wall_x = s_r->posy + s_r->perp_w_d * s_r->raydiry;
	else
		s_r->wall_x = s_r->posx + s_r->perp_w_d * s_r->raydirx;
	s_r->wall_x -= floor((s_r->wall_x));
	s_r->tex_x = (int)(s_r->wall_x * cub->img_textures[s_r->tex_idx]->x);
	if (s_r->side == 0 && s_r->raydirx > 0)
		s_r->tex_x = cub->img_textures[s_r->tex_idx]->x - s_r->tex_x - 1;
	if (s_r->side == 1 && s_r->raydiry < 0)
		s_r->tex_x = cub->img_textures[s_r->tex_idx]->x - s_r->tex_x - 1;
	s_r->tex_x = cub->img_textures[s_r->tex_idx]->x - s_r->tex_x - 1;
	s_r->step = 1.0 * (cub->img_textures[s_r->tex_idx]->y) / (s_r->lineheight);
	s_r->step = s_r->step - MIN_STEP;
	s_r->step_sum = 0.0;
	if (s_r->lineheight - 1 > (s_r->drawend - s_r->drawstart))
		s_r->step_sum = ((cub->img_textures[s_r->tex_idx]->y)
				- (s_r->drawend - s_r->drawstart) * s_r->step) / 2;
}

void	pixels_color(t_c3d *cub, t_ray *s_r)
{
	int	i;

	i = 0;
	ft_calc_tex_x_y(cub, s_r);
	while (i < s_r->drawstart)
		*cub->img[cub->idx_img]->img_tab[s_r->x][i++] = cub->ceil_rgb;
	while (i < s_r->drawend)
	{
		s_r->tex_y = (int)s_r->step_sum;
		*cub->img[cub->idx_img]->img_tab[s_r->x][i++]
			= *cub->img_textures[s_r->tex_idx]->img_tab[s_r->tex_x][s_r->tex_y];
		s_r->step_sum += s_r->step;
	}
	while (i < cub->res_height)
		*cub->img[cub->idx_img]->img_tab[s_r->x][i++] = cub->floor_rgb;
}
