/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseiller <lseiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 13:21:46 by lseiller          #+#    #+#             */
/*   Updated: 2022/06/03 15:33:53 by lseiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_multiple_fork_pipe(int pipefd[2], int argc, char **argv, char **envp)
{
	int		i;
	int		sreadfd;
	pid_t	pid;

	i = 4;
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
	return (i);
}

static char	*strjoin_free_first(char *s1, char *s2)
{
	char	*dest;

	if (!s1 || !s2)
		return (NULL);
	dest = ft_strjoin(s1, s2);
	free(s1);
	return (dest);
}

static char	*gnl_until_limiter(char *limiter, char *final_str, char *gnl_return)
{
	while (ft_strcmp(gnl_return, limiter) && gnl_return)
	{
		free(gnl_return);
		ft_printf("> ");
		gnl_return = get_next_line(0);
		if (!gnl_return)
		{
			free(limiter);
			return (final_str);
		}
		if (ft_strcmp(gnl_return, limiter))
		{
			final_str = strjoin_free_first(final_str, gnl_return);
			if (!final_str)
				return (free_read_limiter(limiter, gnl_return, final_str));
		}
	}
	if (gnl_return)
		free(gnl_return);
	free(limiter);
	return (final_str);
}

char	*read_to_limiter(char *limiter)
{
	char		*gnl_return;
	char		*final_str;

	final_str = NULL;
	limiter = ft_strjoin(limiter, "\n");
	if (!limiter)
		return (NULL);
	ft_printf("> ");
	gnl_return = get_next_line(0);
	if (!gnl_return)
		return (free_read_limiter(limiter, NULL, NULL));
	if (ft_strcmp(gnl_return, limiter))
	{
		final_str = ft_strdup(gnl_return);
		if (!final_str)
			return (free_read_limiter(limiter, gnl_return, final_str));
	}
	if (!ft_strcmp(gnl_return, limiter))
		return (free_read_limiter(limiter, gnl_return, final_str));
	final_str = gnl_until_limiter(limiter, final_str, gnl_return);
	return (final_str);
}

void	ft_pipe_outfile_append(char *file, int fdread, char *argv, char **envp)
{
	char	**path;
	int		fd;

	path = parsing_path(envp);
	if (!path)
	{
		close(fdread);
		exit(17);
	}
	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0666);
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
