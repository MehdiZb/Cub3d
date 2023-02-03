/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chr_in_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzblah <mehdi.zblah@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 16:49:22 by mzblah            #+#    #+#             */
/*   Updated: 2021/05/11 12:25:07 by mzblah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_chr_in_str(const char *src, int chr)
{
	int	i;

	i = -1;
	if (!src)
		return (0);
	while (src[++i])
		if (src[i] == chr)
			return (i + 1);
	return (0);
}
