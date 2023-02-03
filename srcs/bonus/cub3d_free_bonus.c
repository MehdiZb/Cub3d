/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_free_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzblah <mehdi.zblah@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 20:47:29 by mzblah            #+#    #+#             */
/*   Updated: 2021/05/11 13:33:40 by mzblah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_bonus(t_c3d *cub)
{
	int	idx;

	if (cub->mm)
	{
		free_t_image_b(cub->mlx->mlx_ptr, cub->mm->img);
		free(cub->mm);
	}
	if (!cub->hud)
		return ;
	idx = 0;
	while (cub->hud->hud_tex && idx < NB_HUD_TEX)
		free_t_image_b(cub->mlx->mlx_ptr, cub->hud->hud_tex[idx++]);
	if (cub->hud->hud_tex)
		free(cub->hud->hud_tex);
	idx = 0;
	while (cub->hud->weapons_tex && idx < NB_WEAPONS * 2)
		free_t_image_b(cub->mlx->mlx_ptr, cub->hud->weapons_tex[idx++]);
	if (cub->hud->weapons_tex)
		free(cub->hud->weapons_tex);
	if (cub->hud->hud_img)
		free_t_image_b(cub->mlx->mlx_ptr, cub->hud->hud_img);
	if (cub->hud->items)
		free(cub->hud->items);
	free(cub->hud);
}
