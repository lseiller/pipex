/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseiller <lseiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:29:31 by lseiller          #+#    #+#             */
/*   Updated: 2022/06/03 14:19:56 by lseiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	if (argc > 4)
	{
		if (ft_strcmp(argv[1], "here_doc"))
			ft_pipe(argc, argv, envp);
		else if (argc > 5)
			ft_heredoc(argc, argv, envp);
		else
		{
			ft_dprintf(2, "%s: too few arguments\n", argv[0]);
			return (1);
		}
		while (waitpid(-1, 0, 0) != -1)
			;
	}
	else
	{
		ft_dprintf(2, "%s: too few arguments\n", argv[0]);
		return (1);
	}
}

//Exit 10 -> first pipe failed
//// Exit 11 -> first fork failed
//Exit 12 -> first path failed
//Exit 13 -> open infile failed
//Exit 14 -> first exec_cmds failed
//Exit 15 -> inpipe path failed
//Exit 16 -> inpipe exec_cmds failed
//Exit 17 -> last path failed
//Exit 18 -> last open failed
//Exit 19 -> last exec_cmds failed
//Exit 20 -> malloc split_args failed
//Exit 21 -> malloc has_access failed or no such file or directory
//Exit 22 -> dup2 failed
//Exit 23 -> here_doc read failed
//Exit 42 -> close exit init -> pipe failed or something else
