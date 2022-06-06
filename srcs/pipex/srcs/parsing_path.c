/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseiller <lseiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 16:03:47 by lseiller          #+#    #+#             */
/*   Updated: 2022/05/22 15:01:12 by lseiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*search_path(char **envp)
{
	if (ft_strnstr(*envp, "PATH=", 6))
		return (*envp);
	while (*envp++)
	{
		if (ft_strnstr(*envp, "PATH=", 6))
			return (*envp);
	}
	return (NULL);
}

static int	remove_colon(char **path_split)
{
	int		i;
	char	*str_tmp;

	i = 0;
	while (path_split[i])
	{
		str_tmp = ft_strncut(path_split[i], ':', 1);
		if (!str_tmp)
			return (-1);
		if (!path_split[i + 1] && ft_strcmp(str_tmp, path_split[i]))
		{
			free(path_split[i]);
			path_split[i] = str_tmp;
			i++;
			free(path_split[i]);
			str_tmp = ft_calloc(2, sizeof(char));
			if (!str_tmp)
				return (-1);
			*str_tmp = '.';
		}
		free(path_split[i]);
		path_split[i] = str_tmp;
		i++;
	}
	return (0);
}

static char	**current_directory(void)
{
	char	**str;

	str = ft_calloc(2, sizeof(char *));
	if (!str)
		return (NULL);
	*str = ft_calloc(2, sizeof(char));
	if (!*str)
	{
		free (str);
		return (NULL);
	}
	**str = '.';
	return (str);
}

char	**parsing_path(char **envp)
{
	char	*path;
	char	**path_split;

	path = search_path(envp);
	if (!path || !ft_strcmp(path, "PATH="))
		return (current_directory());
	path = ft_strtrim(path, "PATH=");
	if (!path)
		return (NULL);
	if (*path == ':' && !*(path + 1))
	{
		free(path);
		return (current_directory());
	}
	path_split = ft_split_path(path);
	free(path);
	if (!path_split)
		return (NULL);
	if (remove_colon(path_split) == SYSCALL_FAIL)
		ft_free_split(path_split);
	return (path_split);
}
