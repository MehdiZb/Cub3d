/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init_img_textures_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzblah <mehdi.zblah@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 14:19:47 by mzblah            #+#    #+#             */
/*   Updated: 2021/04/10 19:13:13 by mzblah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	ft_init_pointer_tab(t_img *img)
{
	char	*dst;
	int		idx_x;
	int		idx_y;

	idx_x = 0;
	if (!ac((void **)&img->img_tab,
			ft_calloc(img->x, sizeof(unsigned int **))))
		return (-1);
	while (idx_x < img->x)
		if (!ac((void **)&img->img_tab[idx_x++],
				ft_calloc(img->y, sizeof(unsigned int *))))
			return (-1);
	idx_x = 0;
	while (idx_x < img->x)
	{
		idx_y = 0;
		while (idx_y < img->y)
		{
			dst = img->addr + (idx_y * img->line_len + idx_x * (img->bpp_8));
			img->img_tab[idx_x][idx_y++] = (unsigned int *)dst;
		}
		idx_x++;
	}
	return (0);
}

int	ft_load_textures(t_c3d *cub, t_img *tmp, char *file_addr)
{
	if (!ac((void **)&tmp->img,
			mlx_xpm_file_to_image(cub->mlx->mlx_ptr,
				file_addr, &tmp->x, &tmp->y)))
		return (-1005);
	if (!ac((void **)&tmp->addr,
			mlx_get_data_addr(tmp->img, &tmp->bpp,
				&tmp->line_len, &tmp->endian)))
		return (-1005);
	tmp->bpp_8 = tmp->bpp / 8;
	if (ft_init_pointer_tab(tmp))
		return (-2005);
	return (0);
}

int	ft_init_textures(t_c3d *cub, int idx)
{
	int	state;
	int	(*f)(t_c3d*, t_img*, char*);

	f = ft_load_textures;
	if (!ac((void **)&cub->img_textures,
			ft_calloc(NBR_TEX_BNS, sizeof(t_img *))))
		return (-1004);
	while (idx < NBR_TEX_BNS)
		if (!ac((void **)&cub->img_textures[idx++],
				ft_calloc(1, sizeof(t_img))))
			return (-1004);
	if (a(&state, (*f)(cub, cub->img_textures[0], cub->n_t), 9, 0)
		|| (a(&state, (*f)(cub, cub->img_textures[1], cub->e_t), 9, 0))
		|| (a(&state, (*f)(cub, cub->img_textures[2], cub->s_t), 9, 0))
		|| (a(&state, (*f)(cub, cub->img_textures[3], cub->w_t), 9, 0))
		|| (a(&state, (*f)(cub, cub->img_textures[4], cub->sprite_t), 9, 0))
		|| (a(&state, (*f)(cub, cub->img_textures[5], S_SNIPE), 9, 0))
		|| (a(&state, (*f)(cub, cub->img_textures[6], S_NEIN), 9, 0))
		|| (a(&state, (*f)(cub, cub->img_textures[7], S_HEART), 9, 0)))
		return (state);
	return (0);
}

int	ft_init_img(t_c3d *cub, t_img *img)
{
	img->img = mlx_new_image(cub->mlx->mlx_ptr, img->x, img->y);
	if (!(img->img))
		return (-1);
	img->addr = mlx_get_data_addr(img->img, &img->bpp,
			&img->line_len, &img->endian);
	if (!(img->addr))
		return (-1);
	img->bpp_8 = img->bpp / 8;
	if ((ft_init_pointer_tab(img)) == -1)
		return (-3);
	return (0);
}

int	ft_mlx_img_init(t_c3d *cub)
{
	int		idx;
	int		state;
	t_img	*tmp;

	idx = 0;
	cub->img = (t_img **)ft_calloc(MLX_IMG_NBR, sizeof(t_img *));
	if (!(cub->img))
		return (-1000);
	while (idx < MLX_IMG_NBR)
	{
		cub->img[idx] = (t_img *)ft_calloc(1, sizeof(t_img));
		if (!(cub->img[idx]))
			return (-1001);
		tmp = cub->img[idx++];
		tmp->x = cub->res_width;
		tmp->y = cub->res_height;
		if (a(&state, ft_init_img(cub, tmp), 3, 0))
			return (state - 1000);
	}
	return (0);
}
