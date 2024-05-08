/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sidiallo <sidiallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:18:06 by sidiallo          #+#    #+#             */
/*   Updated: 2024/05/07 16:59:49 by sidiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	open_read_file(int fd, char *limiter)
{
	char	*line;

	while (1)
	{
		line = get_next_line(0, 0);
		if (!line)
			break ;
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
			&& ft_strlen(line) - 1 == ft_strlen(limiter))
		{
			free(line);
			get_next_line(0, 1);
			break ;
		}
		ft_putstr_fd(line, fd);
		free(line);
	}
}

void	ft_here_doc(t_pipex *pipex, char *limiter)
{
	int	fd;

	fd = open("here_doc", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("Error: open failed\n", 2);
		return ;
	}
	open_read_file(fd, limiter);
	close(fd);
	pipex->infile = "here_doc";
}
