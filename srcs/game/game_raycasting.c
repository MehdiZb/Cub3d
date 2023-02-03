/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_raycasting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzblah <mehdi.zblah@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 13:53:34 by mzblah            #+#    #+#             */
/*   Updated: 2021/05/30 22:37:09 by mzblah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_init_s_ray(t_c3d *cub)
{
	double	fov;

	fov = 0.66;
	cub->dist_buffer = (double *)ft_calloc(cub->res_width, sizeof(double));
	if (!cub->dist_buffer)
		return (-3001);
	cub->s_ray = (t_ray *)ft_calloc(1, sizeof(*cub->s_ray));
	if (!(cub->s_ray))
		return (-1002);
	ft_bzero((void *)cub->s_ray, sizeof(*cub->s_ray));
	cub->s_ray->posx = (double)cub->pos_x + 0.5;
	cub->s_ray->posy = (double)cub->pos_y + 0.5;
	if (cub->pos_direction == 'W' || cub->pos_direction == 'E')
		cub->s_ray->dirx = d((cub->pos_direction == 'W'), -1, 1);
	else if (cub->pos_direction == 'N' || cub->pos_direction == 'S')
		cub->s_ray->diry = d((cub->pos_direction == 'N'), -1, 1);
	if (cub->pos_direction == 'S' || cub->pos_direction == 'N')
		cub->s_ray->planex = d((cub->pos_direction == 'S'), -fov, fov);
	else if (cub->pos_direction == 'W' || cub->pos_direction == 'E')
		cub->s_ray->planey = d((cub->pos_direction == 'E'), fov, -fov);
	cub->map[cub->pos_y][cub->pos_x] = '0';
	return (0);
}

void	init_delta(t_ray *s_r, double ray_dirx_2, double ray_diry_2)
{
	s_r->mapx = (int)s_r->posx;
	s_r->mapy = (int)s_r->posy;
	if (s_r->raydiry == 0)
		s_r->deltadistx = 0;
	else if (s_r->raydirx == 0)
		s_r->deltadistx = 1;
	else
		s_r->deltadistx = sqrt(1 + (ray_diry_2) / (ray_dirx_2));
	if (s_r->raydirx == 0)
		s_r->deltadisty = 0;
	else if (s_r->raydiry == 0)
		s_r->deltadisty = 1;
	else
		s_r->deltadisty = sqrt(1 + (ray_dirx_2) / (ray_diry_2));
	if (s_r->raydirx < 0 && (a(&s_r->stepx, -1, 9, 0)))
		s_r->sidedistx = (s_r->posx - s_r->mapx) * s_r->deltadistx;
	else if (a(&s_r->stepx, 1, 9, 0))
		s_r->sidedistx = (s_r->mapx + 1.0 - s_r->posx) * s_r->deltadistx;
	if (s_r->raydiry < 0 && a(&s_r->stepy, -1, 9, 0))
		s_r->sidedisty = (s_r->posy - s_r->mapy) * s_r->deltadisty;
	else if (a(&s_r->stepy, 1, 9, 0))
		s_r->sidedisty = (s_r->mapy + 1.0 - s_r->posy) * s_r->deltadisty;
}

static void	while_side(t_c3d *cub, t_ray *s_r)
{
	s_r->hit = 0;
	while (s_r->hit == 0)
	{
		if (s_r->sidedistx < s_r->sidedisty)
		{
			s_r->sidedistx += s_r->deltadistx;
			s_r->mapx += s_r->stepx;
			s_r->side = 0;
		}
		else
		{
			s_r->sidedisty += s_r->deltadisty;
			s_r->mapy += s_r->stepy;
			s_r->side = 1;
		}
		if (cub->map[s_r->mapy][s_r->mapx] == '1')
			s_r->hit = 1;
	}
	if (s_r->side == 0)
		s_r->perp_w_d
			= (s_r->mapx - s_r->posx + (1 - s_r->stepx) / 2) / s_r->raydirx;
	else
		s_r->perp_w_d
			= (s_r->mapy - s_r->posy + (1 - s_r->stepy) / 2) / s_r->raydiry;
}

static void	draw_line_start_end(t_c3d *cub, t_ray *s_ray)
{
	s_ray->lineheight = (int)(cub->res_height / s_ray->perp_w_d);
	s_ray->drawstart = -s_ray->lineheight / 2 + cub->res_height / 2;
	if (s_ray->drawstart < 0)
		s_ray->drawstart = 0;
	s_ray->drawend = s_ray->lineheight / 2 + cub->res_height / 2;
	if (s_ray->drawend >= (int)cub->res_height)
		s_ray->drawend = cub->res_height - 1;
}

void	ft_raycasting_loop(t_c3d *cub, t_ray *s_ray)
{
	s_ray->x = 0;
	while (s_ray->x < cub->res_width)
	{
		s_ray->camerax = 2 * s_ray->x / (double)cub->res_width - 1;
		s_ray->raydirx = s_ray->dirx + s_ray->planex * s_ray->camerax;
		s_ray->raydiry = s_ray->diry + s_ray->planey * s_ray->camerax;
		init_delta(s_ray, (s_ray->raydirx * s_ray->raydirx),
			(s_ray->raydiry * s_ray->raydiry));
		while_side(cub, s_ray);
		draw_line_start_end(cub, s_ray);
		pixels_color(cub, s_ray);
		cub->dist_buffer[s_ray->x] = s_ray->perp_w_d;
		s_ray->x++;
	}
	ft_draw_sprite(cub, s_ray, cub->dist_buffer);
}
