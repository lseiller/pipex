/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseiller <lseiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 14:06:01 by lseiller          #+#    #+#             */
/*   Updated: 2022/06/02 17:27:26 by lseiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <errno.h>
# include <strings.h>
# include <unistd.h>
# include <sys/types.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include "../../libft/includes/libft.h"

enum e_sys_value {
	SYSCALL_FAIL = -1,
	READ,
	WRITE,
};

//parsing_path.c
char	**parsing_path(char **envp);

//parsing_arg.c
char	**ft_split_args(char *args);

//here_doc_tools.c
char	*read_to_limiter(char *limiter);
void	ft_pipe_outfile_append(char *file, int fdread, char *argv, char **envp);
int		ft_multiple_fork_pipe(int pipefd[2], int argc, char **argv,
			char **envp);

//pipex_tools.c
void	ft_pipe_to_pipe(int in, int out, char *argv, char **envp);
void	ft_pipe_outfile(char *file, int fdread, char *argv, char **envp);
void	ft_pipe_infile(char *file, int pipefd[2], char *argv, char **envp);
int		ft_multiple_fork(int pipefd[2], int argc, char **argv, char **envp);

//tools.c
int		ft_dup2(int in, int out);
void	close_exit(int pipefd[2], int sreadfd);
void	exec_cmds(char *argv, char **envp, char **path);
char	*free_read_limiter(char *s1, char *s2, char *s3);

//pipex.c
void	ft_pipe(int argc, char **argv, char**envp);
void	ft_heredoc(int argc, char **argv, char **envp);
#endif
