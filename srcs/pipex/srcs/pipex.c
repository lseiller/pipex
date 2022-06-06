/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseiller <lseiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 15:06:31 by lseiller          #+#    #+#             */
/*   Updated: 2022/06/02 17:23:08 by lseiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_pipe_here_doc(char *heredoc, int pipefd[2], char *argv, char **envp)
{
	int		sec_pipefd[2];

	if (pipe(sec_pipefd) == SYSCALL_FAIL)
	{
		if (heredoc)
			free(heredoc);
		close_exit(pipefd, -1);
	}
	if (heredoc)
	{
		ft_dprintf(sec_pipefd[WRITE], "%s", heredoc);
		free(heredoc);
	}
	close(sec_pipefd[WRITE]);
	close(pipefd[READ]);
	ft_pipe_to_pipe(sec_pipefd[READ], pipefd[WRITE], argv, envp);
}

void	ft_heredoc(int argc, char **argv, char **envp)
{
	char	*heredoc;
	pid_t	pid;
	int		pipefd[2];
	int		i;

	if (pipe(pipefd) == SYSCALL_FAIL)
		exit (10);
	heredoc = read_to_limiter(argv[2]);
	pid = fork();
	if (pid == 0)
		ft_pipe_here_doc(heredoc, pipefd, argv[3], envp);
	free(heredoc);
	if (pid == SYSCALL_FAIL)
		close_exit(pipefd, -1);
	close(pipefd[WRITE]);
	i = 4;
	if (i < argc - 2)
		i = ft_multiple_fork_pipe(pipefd, argc, argv, envp);
	pid = fork();
	if (pid == SYSCALL_FAIL)
		close_exit(NULL, pipefd[READ]);
	if (pid == 0)
		ft_pipe_outfile_append(argv[argc - 1], pipefd[READ], argv[i], envp);
	close(pipefd[READ]);
}

void	ft_pipe(int argc, char **argv, char **envp)
{
	pid_t	pid;
	int		pipefd[2];
	int		i;

	if (pipe(pipefd) == SYSCALL_FAIL)
		exit (10);
	pid = fork();
	if (pid == SYSCALL_FAIL)
		close_exit(pipefd, -1);
	if (pid == 0)
		ft_pipe_infile(argv[1], pipefd, argv[2], envp);
	else
	{
		close(pipefd[WRITE]);
		i = 3;
		if (i < argc - 2)
			i = ft_multiple_fork(pipefd, argc, argv, envp);
		pid = fork();
		if (pid == SYSCALL_FAIL)
			close_exit(NULL, pipefd[READ]);
		if (pid == 0)
			ft_pipe_outfile(argv[argc - 1], pipefd[READ], argv[i], envp);
		close(pipefd[READ]);
	}
	return ;
}
