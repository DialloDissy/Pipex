/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sidiallo <sidiallo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:46:21 by sidiallo          #+#    #+#             */
/*   Updated: 2024/05/07 15:10:20 by sidiallo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipex
{
	char	**cmd;
	char	*infile;
	char	*outfile;
	char	**env;
	int		prev_fd;
	int		infile_fd;
	int		outfile_fd;
	int		pipe_fd[2];
	int		*pid;
	int		cmd_count;
	int		flag_here_doc;

}			t_pipex;

void		ft_pipex_init(t_pipex *pipex, int argc, char **argv, char **env);
int			ft_pipex(t_pipex *pipex);
void		ft_child_process(t_pipex *pipex, int i);
void		ft_parent_process(t_pipex *pipex, int i);
void		ft_execve(char *cmd, t_pipex *pipex);
void		ft_redirection(t_pipex *pipex, int i);
void		ft_open_outfile(t_pipex *pipex, int i);
void		ft_open_infile(t_pipex *pipex, int i);
void		ft_open_files(t_pipex *pipex, int i);
void		ft_free(t_pipex *pipex);
char		*ft_get_path(char *cmd, char **env);
char		*ft_find_path(char **split_path, char *cmd);
int			ft_waitpid(t_pipex *pipex);
void		ft_forfree(char **strf);
void		do_execve(char *cmd, char **split_cmd, t_pipex *pipex);
void		handle_error(void);
void		ft_here_doc(t_pipex *pipex, char *limiter);
void		open_read_file(int fd, char *limiter);

#endif
