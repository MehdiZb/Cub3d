/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_exit_management.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzblah <mehdi.zblah@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 13:53:34 by mzblah            #+#    #+#             */
/*   Updated: 2021/05/30 22:38:14 by mzblah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	free_t_image(void *mlx_ptr, t_img *img)
{
	int	idx_x;

	idx_x = 0;
	if (img)
	{
		if (img->img)
			mlx_destroy_image(mlx_ptr, img->img);
		if (img->img_tab)
		{
			while (idx_x < img->x && img->img_tab[idx_x])
				free(img->img_tab[idx_x++]);
			free(img->img_tab);
		}
		free(img);
	}
}

static void	ft_free_str_tex_map(
	t_c3d *cub, char *tmp_map, t_l_str *u, int i)
{
	if (cub->n_t)
		free(cub->n_t);
	if (cub->s_t)
		free(cub->s_t);
	if (cub->w_t)
		free(cub->w_t);
	if (cub->e_t)
		free(cub->e_t);
	if (cub->sprite_t)
		free(cub->sprite_t);
	if (cub->map)
		while (ac((void **)&tmp_map, *(cub->map))
			&& (ac((void **)cub->map, cub->map[++i]) || 1))
			free(tmp_map);
	if (cub->map)
		free(cub->map);
	while (cub->map_str && (ac((void **)&u, (char *)cub->map_str->next) || !u))
	{
		if (cub->map_str->str)
			free(cub->map_str->str);
		free(cub->map_str);
		cub->map_str = u;
	}
}

static void	ft_free_tab_ray_mlx_ptr(t_c3d *cub, int idx_a, int idx_b, int idx_c)
{
	if (cub->img)
	{
		while (idx_a < MLX_IMG_NBR)
			free_t_image(cub->mlx->mlx_ptr, cub->img[idx_a++]);
		free(cub->img);
	}
	if (cub->img_textures)
	{
		while (idx_b < NBR_TEXTURE)
			free_t_image(cub->mlx->mlx_ptr, cub->img_textures[idx_b++]);
		free(cub->img_textures);
	}
	if (cub->spr_tab)
	{
		while (idx_c < cub->nb_spr && cub->spr_tab[idx_c])
			free(cub->spr_tab[idx_c++]);
		free(cub->spr_tab);
	}
	if (cub->s_ray)
		free(cub->s_ray);
	if (cub->mlx && cub->mlx->mlx_ptr)
	{
		mlx_destroy_display(cub->mlx->mlx_ptr);
		free(cub->mlx->mlx_ptr);
	}
}

int	ft_exit_cub3d(t_c3d *cub, int state)
{
	if (!cub->save && state != -51)
		mlx_destroy_window(cub->mlx->mlx_ptr, cub->mlx->mlx_win);
	if (cub)
		if (cub->dist_buffer)
			free(cub->dist_buffer);
	ft_exit(cub, state);
	exit(state);
	return (state);
}

int	ft_exit(t_c3d *cub, int state)
{
	char	*tmp_map;
	t_l_str	*tmp_l;

	tmp_map = NULL;
	tmp_l = NULL;
	if (cub)
	{
		ft_free_str_tex_map(cub, tmp_map, tmp_l, 0);
		ft_free_tab_ray_mlx_ptr(cub, 0, 0, 0);
		if (cub->mlx)
			free(cub->mlx);
		free(cub);
	}
	if (state < 0)
	{
		ft_putstr_fd("Error\n", 1);
		if (ft_error_message(state, 0, 0) != 0)
		{
			ft_putstr_fd(MSG_FAIL_OPEN_READ, 1);
			return (-1);
		}
	}
	return (state);
}
