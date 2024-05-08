/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_execve.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sidiallo <sidiallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 12:33:31 by sidiallo          #+#    #+#             */
/*   Updated: 2024/05/07 14:19:39 by sidiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_execve(char *cmd, t_pipex *pipex)
{
	char	**split_cmd;

	split_cmd = ft_split(cmd, ' ');
	if (!split_cmd)
	{
		ft_putstr_fd("Error: Split failed\n", 2);
		exit(127);
	}
	if (split_cmd[0] == NULL)
	{
		ft_putstr_fd("Error: Command not found\n", 2);
		ft_forfree(split_cmd);
		free(pipex->pid);
		exit(127);
	}
	cmd = ft_get_path(split_cmd[0], pipex->env);
	if (cmd == NULL)
	{
		ft_putstr_fd("Error: Command not found\n", 2);
		ft_forfree(split_cmd);
		free(pipex->pid);
		exit(127);
	}
	do_execve(cmd, split_cmd, pipex);
}

void	do_execve(char *cmd, char **split_cmd, t_pipex *pipex)
{
	if (execve(cmd, split_cmd, pipex->env) != -1)
	{
		ft_forfree(split_cmd);
		return ;
	}
	perror("Error");
	strerror(errno);
	free(pipex->pid);
	ft_forfree(split_cmd);
	exit(errno);
}

char	*ft_get_path(char *cmd, char **env)
{
	char	**split_path;
	int		i;
	char	*path;

	i = -1;
	if (ft_strchr(cmd, '/') != NULL)
		return (cmd);
	while (env[++i])
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			break ;
	if (!env[i])
	{
		ft_putstr_fd("Error: Path not found\n", 2);
		exit(1);
	}
	split_path = ft_split(env[i] + 5, ':');
	if (!split_path)
	{
		ft_putstr_fd("Error: Split failed\n", 2);
		exit(1);
	}
	path = ft_find_path(split_path, cmd);
	ft_forfree(split_path);
	return (path);
}

char	*ft_find_path(char **split_path, char *cmd)
{
	int		i;
	char	*path;
	char	*tmp;

	i = 0;
	while (split_path[i])
	{
		path = ft_strjoin(split_path[i], "/");
		tmp = path;
		path = ft_strjoin(path, cmd);
		free(tmp);
		if (access(path, F_OK | X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
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
