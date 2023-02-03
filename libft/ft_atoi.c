/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mzblah <mehdi.zblah@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 14:31:53 by Mzblah            #+#    #+#             */
/*   Updated: 2019/09/29 14:31:54 by Mzblah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	unsigned int	i;
	unsigned int	res;
	int				signe;

	i = 0;
	res = 0;
	signe = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
	{
		signe = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
		res = (res * 10) + (str[i++] - 48);
	return (((int)res) * signe);
}
