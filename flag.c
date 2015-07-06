/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwells <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/09 21:48:45 by gwells            #+#    #+#             */
/*   Updated: 2015/02/19 16:28:53 by gwells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_ls.h"

int				endofflag(int ac, char **argv)
{
	int			i;

	i = 1;
	while (i < ac && isflag(i, argv))
	{
		if (!ft_strcmp(argv[i], "--"))
			return (i + 1);
		i++;
	}
	return (i);
}

static void		badflag(char c)
{
	ft_putstr_fd("ft_ls: illegal option -- ", 2);
	ft_putchar_fd(c, 2);
	ft_putchar_fd('\n', 2);
	ft_putendl_fd("usage: ft_ls [-Rltar] [file ...]", 2);
}

int				isflag(int pos, char **argv)
{
	if (pos > 1)
	{
		if (argv[pos][0] == '-' && argv[pos][1] != '\0')
			return (isflag(pos - 1, argv));
	}
	else
	{
		if (argv[pos][0] == '-' && argv[pos][1] != '\0')
			return (1);
		else
			return (0);
	}
	return (0);
}

void			trueflag(char *argv)
{
	char		*flags;
	int			test;
	int			i;

	flags = "l1Rrat";
	flagtochar(argv);
	if (*argv)
		argv++;
	while (*argv)
	{
		i = 0;
		test = 0;
		while (flags[i])
		{
			if (flags[i] == *argv)
				test = 1;
			i++;
		}
		if (!test)
		{
			badflag(*argv);
			exit(EXIT_FAILURE);
		}
		argv++;
	}
}

char			*flagtochar(char *argv)
{
	static char	*str = NULL;
	char		*temp;
	char		*temp2;

	temp = NULL;
	temp2 = NULL;
	if (str != NULL)
	{
		temp = ft_strdup(str);
		ft_strdel(&str);
	}
	if (argv)
		temp2 = ft_strjoin(temp, argv + 1);
	else
		temp2 = ft_strjoin(temp, argv);
	str = ft_strdup(temp2);
	ft_strdel(&temp);
	ft_strdel(&temp2);
	return (str);
}
