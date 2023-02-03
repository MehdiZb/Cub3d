/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_move_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzblah <mzblah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 14:12:08 by mzblah            #+#    #+#             */
/*   Updated: 2021/06/20 10:00:53 by mzblah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <sys/time.h>

void	rotate_view(t_c3d *cub, t_ray *s_r, double old_px, double old_dx)
{
	double	rot_spd;

	rot_spd = (double)cub->ms_diff / 120000;
	if ((cub->is_rot_right == 1 && cub->is_rot_left == 0)
		|| (cub->is_rot_right == 0 && cub->is_rot_left == 1))
	{
		if (cub->is_rot_right == 0)
			rot_spd = -rot_spd;
		s_r->dirx = s_r->dirx * cos(rot_spd / 2)
			- s_r->diry * sin(rot_spd / 2);
		s_r->diry = old_dx * sin(rot_spd / 2)
			+ s_r->diry * cos(rot_spd / 2);
		s_r->planex = s_r->planex * cos(rot_spd / 2)
			- s_r->planey * sin(rot_spd / 2);
		s_r->planey = old_px * sin(rot_spd / 2)
			+ s_r->planey * cos(rot_spd / 2);
	}
}

void	move_forward_backward(t_c3d *cub, t_ray *s_r)
{
	double	m;
	int		(*f)(const char *, int);
	double	x;
	double	y;
	double	p;

	m = (double)cub->ms_diff / 250000;
	f = &ft_chr_in_str;
	x = s_r->dirx * m;
	y = s_r->diry * m;
	p = s_r->posy;
	if (cub->is_mov_forward == 1 && cub->is_mov_backward == 0)
	{
		if ((*f)("0345", cub->map[(int)p][(int)(s_r->posx + (x * 2))]))
			s_r->posx += x;
		if ((*f)("0345", cub->map[(int)(p + (y * 2))][(int)(s_r->posx)]))
			s_r->posy += y;
	}
	else if (cub->is_mov_forward == 0 && cub->is_mov_backward == 1)
	{
		if ((*f)("0345", cub->map[(int)(p)][(int)(s_r->posx - (x * 2))]))
			s_r->posx -= x;
		if ((*f)("0345", cub->map[(int)(p - (y * 2))][(int)(s_r->posx)]))
			s_r->posy -= y;
	}
}

void	move_left_right(t_c3d *cub, t_ray *s_r)
{
	int		(*f)(const char *, int);
	double	x;
	double	y;
	double	m;

	f = &ft_chr_in_str;
	m = (double)cub->ms_diff / 250000;
	x = s_r->posx;
	y = s_r->posy;
	if (cub->is_mov_left == 1)
	{
		if ((*f)("0345", cub->map[(int)y][(int)(x + s_r->diry * (m * 2))]))
			s_r->posx += s_r->diry * m;
		if ((*f)("0345", cub->map[(int)(y - s_r->dirx * (m * 2))][(int)x]))
			s_r->posy -= s_r->dirx * m;
	}
	if (cub->is_mov_right == 1)
	{
		if ((*f)("0345", cub->map[(int)y][(int)(x - s_r->diry * (m * 2))]))
			s_r->posx -= s_r->diry * m;
		if ((*f)("0345", cub->map[(int)(y + s_r->dirx * (m * 2))][(int)x]))
			s_r->posy += s_r->dirx * m;
	}
}

int	key_press(int key_event, t_c3d *cub)
{
	if (key_event == 65307)
		ft_exit_cub3d(cub, 0);
	if (key_event == KEY_W)
		cub->is_mov_forward = 1;
	if (key_event == KEY_S)
		cub->is_mov_backward = 1;
	if (key_event == KEY_A)
		cub->is_mov_left = 1;
	if (key_event == KEY_D)
		cub->is_mov_right = 1;
	if (key_event == ARROW_LEFT)
		cub->is_rot_left = 1;
	if (key_event == ARROW_RIGHT)
		cub->is_rot_right = 1;
	if (key_event == 32)
		cub->hud->shoot_key = 1;
	return (0);
}

int	key_release(int key_event, t_c3d *cub)
{
	if (key_event == KEY_W)
		cub->is_mov_forward = 0;
	if (key_event == KEY_S)
		cub->is_mov_backward = 0;
	if (key_event == KEY_A)
		cub->is_mov_left = 0;
	if (key_event == KEY_D)
		cub->is_mov_right = 0;
	if (key_event == ARROW_LEFT)
		cub->is_rot_left = 0;
	if (key_event == ARROW_RIGHT)
		cub->is_rot_right = 0;
	if (key_event == 32)
		cub->hud->shoot_key = 0;
	if (key_event >= 49 && key_event <= 57)
		cub->hud->item_select
			= t((cub->hud->item_select == key_event - 48),
				0, key_event - 48);
	return (0);
}
