/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lseiller <lseiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 16:26:52 by lseiller          #+#    #+#             */
/*   Updated: 2022/06/03 15:25:19 by lseiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	next_sep(char *args)
{
	const char	*s_ptr = args;
	int			double_quote;
	int			single_quote;

	single_quote = 0;
	double_quote = 0;
	while (*args)
	{
		if (*args == ' ' && *(args + 1) && *(args + 1) != ' '
			&& args - s_ptr > 0 && *(args - 1) != '\\'
			&& single_quote == 0 && double_quote == 0)
			return (args - s_ptr + 1);
		else if (*args == '"' && double_quote == 0)
			double_quote = 1;
		else if (*args == '"')
			double_quote = 0;
		else if (*args == '\'' && single_quote == 0)
			single_quote = 1;
		else if (*args == '\'')
			single_quote = 0;
		args++;
	}
	return (args - s_ptr);
}

static int	nb_of_args(char *args)
{
	int	nb_of_args;

	while (*args == ' ')
		args++;
	nb_of_args = 0;
	while (*args)
	{
		args += next_sep(args);
		nb_of_args++;
	}
	return (nb_of_args);
}

static char	*trim_quote(char *dest)
{
	char	*tmp;

	if (*dest == '\'')
		tmp = ft_strtrim(dest, "'");
	else
		tmp = ft_strtrim(dest, "\"");
	free(dest);
	dest = tmp;
	return (dest);
}

static char	**fill_dest(char **dest, char *args)
{
	int		j;
	int		ret_next_sep;
	int		shift;

	j = 0;
	shift = 1;
	while (*args)
	{
		ret_next_sep = next_sep(args);
		args += ret_next_sep;
		if (!*(args))
			shift = 0;
		dest[j] = ft_substr((args - ret_next_sep), 0, ret_next_sep - shift);
		if (!dest[j])
			return (ft_free_tab(dest, j));
		if (*dest[j] == '\'' || *dest[j] == '"')
			dest[j] = trim_quote(dest[j]);
		j++;
	}
	return (dest);
}

char	**ft_split_args(char *args)
{
	const int	size = nb_of_args(args);
	char		**dest;

	if (!args)
		return (NULL);
	dest = ft_calloc(size + 1, sizeof(char *));
	if (!dest)
		return (NULL);
	return (fill_dest(dest, args));
}
