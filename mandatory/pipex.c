/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sidiallo <sidiallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:46:34 by sidiallo          #+#    #+#             */
/*   Updated: 2024/05/08 20:20:10 by sidiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	ft_waitpid(t_pipex *pipex)
{
	int	i;
	int	status;
	int	exit_status;
	int	pid;

	i = 0;
	while (i < pipex->cmd_count)
	{
		pid = waitpid(-1, &status, 0);
		if (WIFEXITED(status))
			if (pid == pipex->pid[pipex->cmd_count - 1])
				exit_status = WEXITSTATUS(status);
		i++;
	}
	return (exit_status);
}

void	ft_pipex_init(t_pipex *pipex, int argc, char **argv, char **env)
{
	pipex->cmd = &argv[2];
	pipex->env = env;
	pipex->infile = argv[1];
	pipex->outfile = argv[argc - 1];
	pipex->cmd_count = argc - 3;
	pipex->pid = malloc(sizeof(int) * (pipex->cmd_count));
	if (!pipex->pid)
	{
		ft_putstr_fd("Error: malloc failed\n", 2);
		exit(1);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;
	int		ret;

	if (argc != 5)
	{
		ft_putstr_fd("Error: Wrong number of arguments\n", 2);
		exit(1);
	}
	ft_pipex_init(&pipex, argc, argv, env);
	ret = ft_pipex(&pipex);
	free(pipex.pid);
	close(pipex.pipe_fd[0]);
	close(pipex.pipe_fd[1]);
	return (ret);
}
