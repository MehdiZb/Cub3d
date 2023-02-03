/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mzblah <mehdi.zblah@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 20:13:10 by Mzblah            #+#    #+#             */
/*   Updated: 2019/11/07 13:12:46 by mzblah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char			*str;

	str = (char *)malloc(sizeof(char) * (size + 1));
	if (!(str))
		return (0);
	ft_bzero(str, (size + 1));
	return (str);
}
