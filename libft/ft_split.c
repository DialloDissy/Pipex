/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sidiallo <sidiallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 13:00:40 by sidiallo          #+#    #+#             */
/*   Updated: 2024/03/07 14:32:19 by sidiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_forfree(char **strf, int i)
{
	while (i >= 0)
	{
		if (strf[i])
			free(strf[i]);
		i--;
	}
	free(strf);
}

static int	ft_countw(char *str, char c)
{
	int	i;
	int	wrd;

	i = 0;
	wrd = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			wrd++;
			while (str[i] != c && str[i] != '\0')
				i++;
			if (str[i] == '\0')
				return (wrd);
		}
		i++;
	}
	return (wrd);
}

static void	ft_strcpy(char *wrd, char *str, char c, int j)
{
	int	i;

	i = 0;
	while (str[j] && str[j] == c)
		j++;
	while (str[j + i] != c && str[j + i] != '\0')
	{
		wrd[i] = str[j + i];
		i++;
	}
	wrd[i] = '\0';
}

static char	*ft_strforalc(char *str, char c, int *k)
{
	char	*wrd;
	int		j;
	int		i;

	i = 0;
	j = *k;
	wrd = NULL;
	while (str[*k])
	{
		if (str[*k] != c)
		{
			while (str[*k] && str[*k] != c)
			{
				*k += 1;
				i++;
			}
			wrd = (char *)malloc(sizeof(char) * (i + 1));
			if (wrd == NULL)
				return (NULL);
			break ;
		}
		*k += 1;
	}
	ft_strcpy(wrd, str, c, j);
	return (wrd);
}

char	**ft_split(char const *s, char c)
{
	char	**strst;
	int		i;
	int		j;
	int		pos;

	if (s == NULL)
		return (NULL);
	i = 0;
	pos = 0;
	j = ft_countw((char *)s, c);
	strst = (char **)malloc(sizeof(char *) * (j + 1));
	if (strst == NULL)
		return (NULL);
	strst[j] = NULL;
	while (i < j)
	{
		strst[i] = ft_strforalc(((char *)s), c, &pos);
		if (strst[i] == NULL)
		{
			ft_forfree(strst, i);
			return (NULL);
		}
		i++;
	}
	return (strst);
}
