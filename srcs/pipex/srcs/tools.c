/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseiller <lseiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 20:01:51 by lseiller          #+#    #+#             */
/*   Updated: 2022/06/02 17:25:18 by lseiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*free_read_limiter(char *s1, char *s2, char *s3)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	if (s3)
		free(s3);
	return (NULL);
}

static char	*has_access(char **path, char *argv)
{
	char	*cmds;
	char	*strjoined;

	cmds = ft_substr_set(argv, 0, ' ');
	if (!cmds)
		return (NULL);
	if (access(cmds, X_OK) == 0)
		return (cmds);
	while (*path - 1)
	{
		strjoined = ft_strjoin_sep(*path, cmds, '/');
		if (!strjoined)
			break ;
		if (access(strjoined, X_OK) == 0)
		{
			free(cmds);
			return (strjoined);
		}
		free(strjoined);
		path++;
	}
	free (cmds);
	return (NULL);
}

void	exec_cmds(char *argv, char **envp, char **path)
{
	char	**cmd_args;
	char	*cmd_path;

	cmd_args = ft_split_args(argv);
	if (!cmd_args)
	{
		ft_free_split(path);
		exit (20);
	}
	cmd_path = has_access(path, argv);
	ft_free_split(path);
	if (!cmd_path)
	{
		ft_dprintf(2, "pipex: command not found: %s\n", *cmd_args);
		ft_free_split(cmd_args);
		exit (21);
	}
	execve(cmd_path, cmd_args, envp);
	perror("pipex");
	ft_free_split(cmd_args);
	free(cmd_path);
}

int	ft_dup2(int in, int out)
{
	if (dup2(in, STDIN_FILENO) == SYSCALL_FAIL)
	{
		close(in);
		close(out);
		return (-1);
	}
	close(in);
	if (dup2(out, STDOUT_FILENO) == SYSCALL_FAIL)
	{
		close(out);
		return (-1);
	}
	close(out);
	return (0);
}

void	close_exit(int pipefd[2], int sreadfd)
{
	if (pipefd)
	{
		close(pipefd[READ]);
		close(pipefd[WRITE]);
	}
	if (sreadfd >= 0)
		close(sreadfd);
	perror("pipex");
	exit (42);
}
