/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzblah <mehdi.zblah@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 13:53:34 by mzblah            #+#    #+#             */
/*   Updated: 2021/05/30 22:36:17 by mzblah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	game_loop(t_c3d *cub)
{
	ft_raycasting_loop(cub, cub->s_ray);
	mlx_put_image_to_window(cub->mlx->mlx_ptr, cub->mlx->mlx_win,
		cub->img[cub->idx_img++]->img, 0, 0);
	cub->idx_img = t((cub->idx_img == MLX_IMG_NBR), 0, cub->idx_img);
	move_forward_backward(cub, cub->s_ray);
	move_left_right(cub, cub->s_ray);
	rotate_view(cub, cub->s_ray, cub->s_ray->planex, cub->s_ray->dirx);
	return (0);
}

static int	ft_init_mlx_window_imgs(t_c3d *cub, int x, int y)
{
	int	state;

	cub->mlx = (t_mlx *)ft_calloc(1, sizeof(t_mlx));
	if (!(cub->mlx))
		return (-122);
	cub->mlx->mlx_ptr = mlx_init();
	if (!(cub->mlx->mlx_ptr))
		return (-50);
	mlx_get_screen_size(cub->mlx->mlx_ptr, &x, &y);
	cub->res_width = t((cub->res_width > x && !cub->save), x, cub->res_width);
	cub->res_height
		= t((cub->res_height > y && !cub->save), y, cub->res_height);
	cub->mlx->mlx_win = mlx_new_window(cub->mlx->mlx_ptr,
			cub->res_width, cub->res_height, "Cub3D");
	if (!(cub->mlx->mlx_win))
		return (ft_exit_cub3d(cub, -51));
	if (a(&state, ft_mlx_img_init(cub), 2, 0))
		return (ft_exit_cub3d(cub, state));
	if (a(&state, ft_init_s_ray(cub), 2, 0))
		return (ft_exit_cub3d(cub, state));
	if (a(&state, ft_init_textures_normal(cub), 9, 0))
		return (ft_exit_cub3d(cub, state));
	return (0);
}

static void	ft_bmp_header(t_c3d *cub, int fd)
{
	int	tab[6];

	write(fd, "BM", 2);
	tab[0] = 14 + 40 + 4 * cub->res_width * cub->res_height;
	write(fd, &tab[0], 4);
	tab[1] = 0;
	write(fd, &tab[1], 4);
	tab[2] = 54;
	write(fd, &tab[2], 4);
	tab[3] = 40;
	write(fd, &tab[3], 4);
	write(fd, &cub->res_width, 4);
	write(fd, &cub->res_height, 4);
	tab[4] = 1;
	write(fd, &tab[4], 2);
	write(fd, &cub->img[cub->idx_img]->bpp, 2);
	ft_bzero((void *)tab, sizeof(int) * 6);
	write(fd, &tab[0], 24);
}

static int	ft_save(t_c3d *cub)
{
	int	fd;
	int	x;
	int	y;

	y = cub->res_height - 1;
	if (a(&fd, open("./first_frame.bmp", O_CREAT | O_WRONLY | O_TRUNC), 3, 0))
		return (-5000);
	ft_bmp_header(cub, fd);
	while (y >= 0)
	{
		x = 0;
		while (x < cub->res_width)
			write(fd, cub->img[cub->idx_img]->img_tab[x++][y], 4);
		y--;
	}
	system("chmod 777 first_frame.bmp");
	return (0);
}

int	game_init(t_c3d *cub)
{
	int	state;

	state = ft_init_mlx_window_imgs(cub, 0, 0);
	if (state)
		return (state);
	if (cub->save)
	{
		ft_raycasting_loop(cub, cub->s_ray);
		ft_exit_cub3d(cub, ft_save(cub));
	}
	mlx_hook(cub->mlx->mlx_win, 33, 1L << 17, ft_exit_inutile, cub);
	mlx_hook(cub->mlx->mlx_win, 2, 1L << 0, key_press, cub);
	mlx_hook(cub->mlx->mlx_win, 3, 1L << 1, key_release, cub);
	mlx_loop_hook(cub->mlx->mlx_ptr, game_loop, cub);
	mlx_loop(cub->mlx->mlx_ptr);
	return (0);
}
