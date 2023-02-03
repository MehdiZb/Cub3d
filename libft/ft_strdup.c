/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mzblah <mehdi.zblah@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 12:54:04 by Mzblah            #+#    #+#             */
/*   Updated: 2019/11/12 15:31:50 by mzblah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*ret_str;
	int		len_str;
	int		i;

	len_str = ft_strlen(str);
	i = 0;
	ret_str = ft_strnew(len_str);
	if (!(ret_str))
		return (0);
	while (i < len_str)
	{
		ret_str[i] = str[i];
		i++;
	}
	return (ret_str);
}
