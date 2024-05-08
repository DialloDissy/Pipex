/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_pip.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sidiallo <sidiallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:56:12 by sidiallo          #+#    #+#             */
/*   Updated: 2024/05/08 20:21:08 by sidiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	ft_pipex(t_pipex *pipex)
{
	int	i;
	int	ret;

	i = 0;
	pipex->prev_fd = -1;
	while (i < pipex->cmd_count)
	{
		pipe(pipex->pipe_fd);
		pipex->pid[i] = fork();
		if (pipex->pid[i] == -1)
		{
			ft_putstr_fd("Error: Fork failed\n", 2);
			return (1);
		}
		if (pipex->pid[i] == 0)
			ft_child_process(pipex, i);
		else
			ft_parent_process(pipex, i);
		i++;
	}
	ret = ft_waitpid(pipex);
	return (ret);
}

void	ft_child_process(t_pipex *pipex, int i)
{
	ft_redirection(pipex, i);
	if (i == 0 || i == pipex->cmd_count - 1)
		ft_open_files(pipex, i);
	ft_execve(pipex->cmd[i], pipex);
}

void	ft_parent_process(t_pipex *pipex, int i)
{
	close(pipex->pipe_fd[1]);
	if (pipex->prev_fd != -1)
		close(pipex->prev_fd);
	pipex->prev_fd = pipex->pipe_fd[0];
	if (i == pipex->cmd_count - 1)
	{
		close(pipex->pipe_fd[0]);
		close(pipex->pipe_fd[1]);
		close(pipex->prev_fd);
	}
}

void	ft_redirection(t_pipex *pipex, int i)
{
	if (i == 0)
	{
		close(pipex->pipe_fd[0]);
		dup2(pipex->pipe_fd[1], 1);
		close(pipex->pipe_fd[1]);
	}
	else if (i == pipex->cmd_count - 1)
	{
		close(pipex->pipe_fd[1]);
		dup2(pipex->prev_fd, 0);
		close(pipex->prev_fd);
	}
	else
	{
		dup2(pipex->prev_fd, 0);
		dup2(pipex->pipe_fd[1], 1);
		close(pipex->pipe_fd[0]);
	}
}

void	ft_open_files(t_pipex *pipex, int i)
{
	if (i == 0)
	{
		pipex->infile_fd = open(pipex->infile, O_RDONLY);
		if (pipex->infile_fd == -1)
		{
			ft_putstr_fd("Error: Open failed\n", 2);
			free(pipex->pid);
			exit(127);
		}
		dup2(pipex->infile_fd, 0);
		close(pipex->infile_fd);
	}
	else if (i == pipex->cmd_count - 1)
	{
		pipex->outfile_fd = open(pipex->outfile, O_WRONLY | O_CREAT | O_TRUNC,
				0644);
		if (pipex->outfile_fd == -1)
		{
			ft_putstr_fd("Error: Open failed\n", 2);
			free(pipex->pid);
			exit(127);
		}
		dup2(pipex->outfile_fd, 1);
		close(pipex->outfile_fd);
	}
}
