/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzblah <mehdi.zblah@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 12:35:03 by mzblah            #+#    #+#             */
/*   Updated: 2021/05/30 23:05:28 by mzblah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

//supprimer l'executable cub
// ajouter quelques maps
// refaire une norminette complete .h .c

int	a(int *a, int b, int c, int d)
{
	*a = b;
	if (c == 0)
		return (0);
	if (c == 9)
		return (*a);
	if (c == 1)
		return (*a == d);
	if (c == 2)
		return (*a != d);
	if (c == 3)
		return (*a < d);
	if (c == 4)
		return (*a > d);
	return (0);
}

char	*ac(void **a, void *b)
{
	*a = b;
	return (*a);
}

int	t(int c, int a, int b)
{
	if (c)
		return (a);
	return (b);
}

double	d(int c, double a, double b)
{
	if (c)
		return (a);
	return (b);
}

int	main(int argc, char **argv)
{
	t_c3d	*cub;
	int		state;

	if (argc != 2)
		return (ft_exit(NULL, -10));
	state = ft_parse_cub(&cub, argv[1], 0);
	if (state < 0)
		return (ft_exit(cub, state));
	state = game_init(cub);
	if (state != 0)
		return (ft_exit(cub, state));
	return (state);
}
