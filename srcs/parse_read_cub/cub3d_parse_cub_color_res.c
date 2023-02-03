/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_parse_cub_color_res.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzblah <mehdi.zblah@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/19 13:53:34 by mzblah            #+#    #+#             */
/*   Updated: 2021/05/30 22:36:54 by mzblah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	ft_atoi_rgb(const char *str)
{
	unsigned int	i;
	unsigned int	res;

	i = 0;
	res = 0;
	while (ft_isdigit(str[i]))
		res = (res * 10) + (str[i++] - 48);
	return (t((i == 0 || i > 3 || res > 255), -1, (int)res));
}

static int	ft_r_g_b_to_rgb(char *str, int i)
{
	int	aa;
	int	b;
	int	c;

	if (str[i] != ' ')
		return (-1);
	while (str[i] == ' ')
		i++;
	if (a(&aa, ft_atoi_rgb(str + i), 1, -1))
		return (-1);
	while (ft_isdigit(str[i]))
		i++;
	if (skip_spaces_comma(str, &i) || a(&b, ft_atoi_rgb(str + i), 1, -1))
		return (-1);
	while (ft_isdigit(str[i]))
		i++;
	if (skip_spaces_comma(str, &i) || a(&c, ft_atoi_rgb(str + i), 1, -1))
		return (-1);
	while (ft_isdigit(str[i]))
		i++;
	return (t(!str[i], (aa * 65536 + b * 256 + c), -1));
}

int	ft_set_color_and_resolution(t_c3d *cub, char *str)
{
	size_t	i;

	i = 1;
	cub->res_width = 1280;
	cub->res_height = 720;
	cub->is_res_set = 1;
	if (str[0] == 'C' && !cub->is_c_rgb_set)
		if (a(&cub->is_c_rgb_set, 1, 9, 0)
			&& (a(&cub->ceil_rgb, ft_r_g_b_to_rgb(str, i), 2, -1)))
			return (0);
	if (str[0] == 'F' && !cub->is_f_rgb_set)
		if (a(&cub->is_f_rgb_set, 1, 9, 0)
			&& (a(&cub->floor_rgb, ft_r_g_b_to_rgb(str, i), 2, -1)))
			return (0);
	return (-106);
}
