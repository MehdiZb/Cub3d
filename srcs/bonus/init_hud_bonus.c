/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hud_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzblah <mehdi.zblah@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 11:57:52 by mzblah            #+#    #+#             */
/*   Updated: 2021/04/14 21:47:57 by mzblah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_init_hud_textures(t_c3d *cub)
{
	int	i;

	if (!ac((void **)&cub->hud, ft_calloc(1, sizeof(t_hud))))
		return (-10600);
	if (!ac((void **)&cub->hud->hud_tex,
			(ft_calloc(NB_HUD_TEX, sizeof(t_img *)))))
		return (-10601);
	i = 0;
	while (i < NB_HUD_TEX)
		if (!ac((void **)&cub->hud->hud_tex[i++], ft_calloc(1, sizeof(t_img))))
			return (-10602);
	if (a(&i, ft_load_textures(cub, cub->hud->hud_tex[MC_BAR], S_BAR), 3, 0))
		return (t((i > -2000), i - 9600, i - 8601));
	if (a(&i, ft_load_textures(cub, cub->hud->hud_tex[HP_FULL], S_FULL), 3, 0))
		return (t((i > -2000), i - 9600, i - 8601));
	if (a(&i, ft_load_textures(cub, cub->hud->hud_tex[HP_HALF], S_HALF), 3, 0))
		return (t((i > -2000), i - 9600, i - 8601));
	if (a(&i, ft_load_textures(cub, cub->hud->hud_tex[HP_VOID], S_VOID), 3, 0))
		return (t((i > -2000), i - 9600, i - 8601));
	if (a(&i, ft_load_textures
			(cub, cub->hud->hud_tex[ICN_SNIPE], ADR_I_SNIPE), 3, 0))
		return (t((i > -2000), i - 9600, i - 8601));
	return (0);
}

int	ft_init_hud_img(t_c3d *cub)
{
	int	state;
	int	x;
	int	y;

	cub->hud->hud_img = (t_img *)ft_calloc(1, sizeof(t_img));
	if (!(cub->hud->hud_img))
		return (-10610);
	cub->hud->hud_img->x = cub->hud->hud_tex[MC_BAR]->x;
	cub->hud->hud_img->y = cub->hud->hud_tex[MC_BAR]->y
		+ cub->hud->hud_tex[HP_FULL]->y;
	if (a(&state, ft_init_img(cub, cub->hud->hud_img), 3, 0))
		return (state - 10606);
	x = 0;
	while (x < cub->hud->hud_img->x)
	{
		y = 0;
		while (y < cub->hud->hud_img->y)
			*cub->hud->hud_img->img_tab[x][y++] = 0xff000000;
		x++;
	}
	return (0);
}

int	ft_init_weapons_textures(t_c3d *cub)
{
	int	state;
	int	idx;

	cub->hud->weapons_tex
		= (t_img **)ft_calloc(1 * 2, sizeof(t_img *));
	if (!(cub->hud->weapons_tex))
		return (-10612);
	idx = 0;
	while (idx < NB_WEAPONS * 2)
	{
		cub->hud->weapons_tex[idx]
			= (t_img *)ft_calloc(1, sizeof(t_img));
		if (!(cub->hud->weapons_tex[idx++]))
			return (-10612);
	}
	if (a(&state, ft_load_textures(cub,
				cub->hud->weapons_tex[W_SNIPE], ADR_W_SNIPE), 3, 0))
		return (t((state > -2000), state - 9700, state - 8701));
	if (a(&state, ft_load_textures(cub,
				cub->hud->weapons_tex[H_SNIPE], ADR_H_SNIPE), 3, 0))
		return (t((state > -2000), state - 9700, state - 8701));
	return (0);
}
