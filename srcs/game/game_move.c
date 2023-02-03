/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzblah <mehdi.zblah@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 14:12:08 by mzblah            #+#    #+#             */
/*   Updated: 2021/03/27 21:57:42 by mzblah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	rotate_view(t_c3d *cub, t_ray *s_r, double old_px, double old_dx)
{
	double	tmp_rot_speed;

	if ((cub->is_rot_right == 1 && cub->is_rot_left == 0)
		|| (cub->is_rot_right == 0 && cub->is_rot_left == 1))
	{
		tmp_rot_speed = -ROT_SPEED;
		if (cub->is_rot_right)
			tmp_rot_speed = ROT_SPEED;
		s_r->dirx = s_r->dirx * cos(tmp_rot_speed / 2)
			- s_r->diry * sin(tmp_rot_speed / 2);
		s_r->diry = old_dx * sin(tmp_rot_speed / 2)
			+ s_r->diry * cos(tmp_rot_speed / 2);
		s_r->planex = s_r->planex * cos(tmp_rot_speed / 2)
			- s_r->planey * sin(tmp_rot_speed / 2);
		s_r->planey = old_px * sin(tmp_rot_speed / 2)
			+ s_r->planey * cos(tmp_rot_speed / 2);
	}
}

void	move_forward_backward(t_c3d *cub, t_ray *s_r)
{
	int		(*f)(const char *, int);
	double	x;
	double	y;

	f = &ft_chr_in_str;
	x = s_r->dirx * MOV_SPEED;
	y = s_r->diry * MOV_SPEED;
	if (cub->is_mov_forward == 1 && cub->is_mov_backward == 0)
	{
		if ((*f)("03", cub->map[(int)s_r->posy][(int)(s_r->posx + (x * 2))]))
			s_r->posx += x;
		if ((*f)("03", cub->map[(int)(s_r->posy + (y * 2))][(int)(s_r->posx)]))
			s_r->posy += y;
	}
	else if (cub->is_mov_forward == 0 && cub->is_mov_backward == 1)
	{
		if ((*f)("03", cub->map[(int)(s_r->posy)][(int)(s_r->posx - (x * 2))]))
			s_r->posx -= x;
		if ((*f)("03", cub->map[(int)(s_r->posy - (y * 2))][(int)(s_r->posx)]))
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
	x = s_r->posx;
	y = s_r->posy;
	m = MOV_SPEED;
	if (cub->is_mov_left == 1)
	{
		if ((*f)("03", cub->map[(int)y][(int)(x + s_r->diry * (m * 2))]))
			s_r->posx += s_r->diry * m;
		if ((*f)("03", cub->map[(int)(y - s_r->dirx * (m * 2))][(int)x]))
			s_r->posy -= s_r->dirx * m;
	}
	if (cub->is_mov_right == 1)
	{
		if ((*f)("03", cub->map[(int)y][(int)(x - s_r->diry * (m * 2))]))
			s_r->posx -= s_r->diry * m;
		if ((*f)("03", cub->map[(int)(y + s_r->dirx * (m * 2))][(int)x]))
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
	return (0);
}
