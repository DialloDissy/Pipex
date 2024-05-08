/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sidiallo <sidiallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:15:58 by sidiallo          #+#    #+#             */
/*   Updated: 2023/11/27 11:52:28 by sidiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str_a;
	unsigned char	*str_b;
	size_t			i;

	i = 0;
	str_a = (unsigned char *)s1;
	str_b = (unsigned char *)s2;
	while (0 < n)
	{
		if (str_a[i] != str_b[i])
			return (str_a[i] - str_b[i]);
		i++;
		n--;
	}
	return (0);
}
