/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sidiallo <sidiallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:46:34 by sidiallo          #+#    #+#             */
/*   Updated: 2024/05/08 20:21:37 by sidiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	ft_open_files(t_pipex *pipex, int i)
{
	if (i == 0)
		ft_open_infile(pipex, i);
	else if (i == pipex->cmd_count - 1)
		ft_open_outfile(pipex, i);
}

void	ft_forfree(char **strf)
{
	int	i;

	i = 0;
	while (strf[i])
	{
		if (strf[i])
			free(strf[i]);
		i++;
	}
	free(strf);
}

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
	if (pipex->flag_here_doc == 1)
	{
		pipex->cmd_count = argc - 4;
		pipex->cmd = &argv[3];
	}
	else
	{
		pipex->cmd_count = argc - 3;
		pipex->cmd = &argv[2];
	}
	pipex->env = env;
	pipex->infile = argv[1];
	pipex->outfile = argv[argc - 1];
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

	pipex.flag_here_doc = 0;
	if ((argc < 5) || (argc == 5 && strcmp(argv[1], "here_doc") == 0))
	{
		ft_putstr_fd("Error: Wrong number of arguments\n", 2);
		exit(1);
	}
	if (strcmp(argv[1], "here_doc") == 0)
	{
		pipex.flag_here_doc = 1;
		ft_here_doc(&pipex, argv[2]);
	}
	ft_pipex_init(&pipex, argc, argv, env);
	ret = ft_pipex(&pipex);
	free(pipex.pid);
	return (ret);
}
