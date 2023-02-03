/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzblah <mehdi.zblah@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/05 16:57:27 by mzblah            #+#    #+#             */
/*   Updated: 2021/03/28 19:15:37 by mzblah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	ft_set_minimap(t_c3d *cub, t_mm *mm)
{
	int	x;
	int	y;

	x = -1;
	while (++x < mm->img->x)
	{
		y = -1;
		while (++y < mm->img->y)
			*mm->img->img_tab[x][y] = 0xFF808080;
	}
	x = mm->map_draw_x_start - 1;
	while (++x < mm->map_draw_x_end)
	{
		y = mm->map_draw_y_start - 1;
		while (++y < mm->map_draw_y_end)
		{
			if (cub->map
				[y / mm->square_height - 7][x / mm->square_width - 7] == '1')
				*mm->img->img_tab[x][y] = 0xFFFFFFFF;
			else
				*mm->img->img_tab[x][y] = 0xFF65ab23;
		}
	}
}

int	ft_init_mm(t_c3d *cub)
{
	int	state;

	if (!ac((void **)&cub->mm, ft_calloc(1, sizeof(t_mm))))
		return (-10000);
	if (!ac((void **)&cub->mm->img, ft_calloc(1, sizeof(t_img))))
		return (-10001);
	cub->mm->draw_x_start = cub->res_width / 21.32;
	cub->mm->draw_y_start = cub->res_height / 12;
	cub->mm->width = cub->res_width / 8;
	cub->mm->height = cub->res_height / 4.5;
	cub->mm->draw_x_end = cub->mm->draw_x_start + cub->mm->width;
	cub->mm->draw_y_end = cub->mm->draw_y_start + cub->mm->height;
	cub->mm->square_width = cub->mm->width / 14;
	cub->mm->square_height = cub->mm->height / 14;
	cub->mm->img->x = (cub->mm->square_width) * (cub->map_width + 14);
	cub->mm->img->y = (cub->mm->square_height) * (cub->map_height + 14);
	cub->mm->map_draw_x_start = cub->mm->square_width * 7;
	cub->mm->map_draw_y_start = cub->mm->square_height * 7;
	cub->mm->map_draw_x_end = (cub->mm->square_width) * (cub->map_width + 7);
	cub->mm->map_draw_y_end = (cub->mm->square_height) * (cub->map_height + 7);
	if (a(&state, ft_init_img(cub, cub->mm->img), 9, 0))
		return (state - 10500);
	ft_set_minimap(cub, cub->mm);
	return (0);
}

static void	ft_draw_dot(t_c3d *cub, t_mm *mm)
{
	int	x_start;
	int	y_start;
	int	x_end;
	int	y_end;

	x_start = (mm->draw_x_start + (mm->width / 2)) - mm->square_width / 6;
	x_end = (mm->draw_x_start + (mm->width / 2)) + mm->square_width / 6;
	y_end = (mm->draw_y_start + (mm->height / 2)) + mm->square_height / 6;
	while (x_start < x_end)
	{
		y_start = (mm->draw_y_start + (mm->height / 2)) - mm->square_height / 6;
		while (y_start < y_end)
			*cub->img[cub->idx_img]->img_tab[x_start][y_start++] = 0xFF0000;
		x_start++;
	}
}

int	ft_draw_minimap(t_c3d *cub)
{
	int	x;
	int	y;
	int	x_start;
	int	y_start;

	x_start = (cub->s_ray->posx) * cub->mm->square_width - 2.5 - 1;
	x = cub->mm->draw_x_start - 1;
	while (++x < cub->mm->draw_x_end)
	{
		y_start = cub->s_ray->posy * cub->mm->square_height - 2.5;
		++x_start;
		y = cub->mm->draw_y_start - 1;
		while (++y < cub->mm->draw_y_end)
			*cub->img[cub->idx_img]->img_tab[x][y]
				= *cub->mm->img->img_tab[x_start][y_start++];
	}
	ft_draw_dot(cub, cub->mm);
	return (0);
}
