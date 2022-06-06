/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseiller <lseiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:05:26 by lseiller          #+#    #+#             */
/*   Updated: 2022/06/02 14:27:28 by lseiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_pipe_infile(char *file, int pipefd[2], char *argv, char **envp)
{
	char	**path;
	int		fd;

	path = parsing_path(envp);
	close(pipefd[READ]);
	if (!path)
	{
		close(pipefd[WRITE]);
		exit(12);
	}
	fd = open(file, O_RDONLY);
	if (fd == SYSCALL_FAIL)
	{
		perror("pipex");
		ft_free_split(path);
		close(pipefd[WRITE]);
		exit (13);
	}
	ft_dup2(fd, pipefd[WRITE]);
	exec_cmds(argv, envp, path);
	exit (14);
}

void	ft_pipe_to_pipe(int in, int out, char *argv, char **envp)
{
	char	**path;

	path = parsing_path(envp);
	if (!path)
	{
		close(out);
		close(in);
		exit (15);
	}
	ft_dup2(in, out);
	exec_cmds(argv, envp, path);
	exit (16);
}

void	ft_pipe_outfile(char *file, int fdread, char *argv, char **envp)
{
	char	**path;
	int		fd;

	path = parsing_path(envp);
	if (!path)
	{
		close(fdread);
		exit(17);
	}
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == SYSCALL_FAIL)
	{
		perror("pipex");
		ft_free_split(path);
		close(fdread);
		exit (18);
	}
	ft_dup2(fdread, fd);
	exec_cmds(argv, envp, path);
	exit (19);
}

int	ft_multiple_fork(int pipefd[2], int argc, char **argv, char **envp)
{
	int		i;
	int		sreadfd;
	pid_t	pid;

	i = 3;
	while (i < argc - 2)
	{
		sreadfd = pipefd[READ];
		if (pipe(pipefd) == SYSCALL_FAIL)
			close_exit(NULL, sreadfd);
		pid = fork();
		if (pid == SYSCALL_FAIL)
			close_exit(pipefd, sreadfd);
		if (pid == 0)
		{
			close(pipefd[READ]);
			ft_pipe_to_pipe(sreadfd, pipefd[WRITE], argv[i], envp);
		}
		close(pipefd[WRITE]);
		close(sreadfd);
		i++;
	}
	close(pipefd[WRITE]);
	close(sreadfd);
	return (i);
}
