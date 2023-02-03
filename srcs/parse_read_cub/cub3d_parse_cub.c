/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_parse_cub.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzblah <mehdi.zblah@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 13:53:34 by mzblah            #+#    #+#             */
/*   Updated: 2021/05/30 22:28:47 by mzblah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	ft_set_textures(t_c3d *cub, char *str)
{
	size_t	i;

	if (!str[0] || !str[1])
		return (-106);
	i = t((str[0] == 'S' && str[1] == ' '), 1, 2);
	while (str[i] == ' ')
		++i;
	if (i == (size_t)t((str[0] == 'S' && str[1] == ' '), 1, 2))
		return (-106);
	if (str[0] == 'N' && str[1] == 'O' && !cub->n_t)
		if (ac((void **)&cub->n_t, ft_strdup(str + i)))
			return (t((cub->n_t != 0), 0, -106));
	if (str[0] == 'S' && str[1] == 'O' && !cub->s_t)
		if (ac((void **)&cub->s_t, ft_strdup(str + i)))
			return (t((cub->s_t != 0), 0, -106));
	if (str[0] == 'W' && str[1] == 'E' && !cub->w_t)
		if (ac((void **)&cub->w_t, ft_strdup(str + i)))
			return (t((cub->w_t != 0), 0, -106));
	if (str[0] == 'E' && str[1] == 'A' && !cub->e_t)
		if (ac((void **)&cub->e_t, ft_strdup(str + i)))
			return (t((cub->e_t != 0), 0, -106));
	return (-107);
}

static int	ft_read_cub(t_c3d *cub, int fd, int idx_loop, int st)
{
	char	*str;
	int		idx;

	while (st >= 0 && (a(&st, get_next_line(fd, &str), 4, 0)))
	{
		if (idx_loop++ == 0 && (!str[0]))
			st = -105;
		idx = 0;
		while (str[idx] == ' ')
			idx++;
		if (str[idx] == 'F' || str[idx] == 'C')
			st = ft_set_color_and_resolution(cub, str + idx);
		else if (str[idx] >= 'A' && str[idx] <= 'Z')
			st = ft_set_textures(cub, str + idx);
		else if (str[idx] == '1' || str[idx] == ' ')
			st = ft_parse_map(cub, fd, &str);
		else if (str[idx])
			st = -107;
		if (str)
		{
			free(str);
			str = NULL;
		}
	}
	return (t((st == -1 || ft_keep_reading_gnl(fd, &str) == -1), 104, st));
}

static int	ft_check_cub(t_c3d *cub)
{
	if (!cub)
		return (-200);
	if (!cub->map || !cub->pos_direction)
		return (t((!cub->map), -201, -202));
	if (!cub->is_f_rgb_set || !cub->is_c_rgb_set)
		return (t((!cub->is_f_rgb_set), -204, -204));
	if (!cub->n_t || !cub->s_t || !cub->w_t || !cub->e_t)
		return (-206);
	return (1);
}

int	ft_parse_cub(t_c3d **cub, char *cub_path, char *argv2)
{
	int		fd;
	int		p_ln;
	int		state;

	(void)argv2;
	*cub = 0;
	if (a(&p_ln, ft_strlen(cub_path), 3, 5) || cub_path[p_ln - 5] == '/')
		return (-101);
	if (ft_strncmp(EXTENSION, cub_path + (p_ln - 4), EXTENSION_LENGTH))
		return (-101);
	if (a(&fd, open(cub_path, O_RDONLY), 1, -1))
		return (-102);
	*cub = (t_c3d *)malloc(sizeof(**cub));
	if (!(*cub))
		return (-103);
	ft_bzero((void *)*cub, sizeof(t_c3d));
	if (a(&state, ft_read_cub(*cub, fd, 0, 999), 3, 0))
		return (state);
	state = ft_check_cub(*cub);
	return (state);
}
