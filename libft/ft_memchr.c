/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sidiallo <sidiallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:43:53 by sidiallo          #+#    #+#             */
/*   Updated: 2023/11/23 15:23:31 by sidiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	oct;
	size_t			i;

	i = 0;
	str = (unsigned char *)s;
	oct = (unsigned char)c;
	while (i < n)
	{
		if (str[i] == oct)
			return (str + i);
		i++;
	}
	return (NULL);
}
