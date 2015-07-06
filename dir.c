/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwells <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/14 15:40:36 by gwells            #+#    #+#             */
/*   Updated: 2015/01/25 10:02:23 by gwells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdlib.h>
#include <sys/errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

void				noarg(char *path)
{
	if (!ft_strcmp("", path))
	{
		ft_putendl_fd("ft_ls: fts_open: No such file or directory", 2);
		exit(EXIT_FAILURE);
	}
}

t_dlist				*nrep(int ac, char **argv, t_env *env, t_opt *opt)
{
	t_dlist			*norep;
	int				pos;

	norep = ft_dlstnew();
	pos = endofflag(ac, argv);
	while (ac != pos)
	{
		if (statut(argv[pos], opt) == 1)
		{
			env->norep = 1;
			nrep_insertion(norep, argv[pos]);
		}
		pos++;
	}
	return (norep);
}

t_dlist				*isfile(int ac, char **argv, t_opt *opt, t_env *env)
{
	t_dlist			*lsfile;
	int				pos;

	lsfile = ft_dlstnew();
	pos = endofflag(ac, argv);
	while (ac != pos)
	{
		if (statut(argv[pos], opt) == -1)
		{
			if (!opt->t)
				ascii_insertion(lsfile, argv[pos], NULL);
			else
				time_insertion(lsfile, argv[pos], NULL);
			env->file = 1;
		}
		pos++;
	}
	return (lsfile);
}

t_dlist				*isrep(int ac, char **argv, t_opt *opt, t_env *env)
{
	t_dlist			*lsrep;
	int				pos;

	lsrep = ft_dlstnew();
	pos = endofflag(ac, argv);
	while (pos != ac)
	{
		if (statut(argv[pos], opt) == 0)
		{
			if (!opt->t)
				ascii_insertion(lsrep, argv[pos], NULL);
			else
				time_insertion(lsrep, argv[pos], NULL);
			env->rep = 1;
		}
		pos++;
	}
	if (ac == endofflag(ac, argv))
		ascii_insertion(lsrep, ".", NULL);
	return (lsrep);
}

t_env				*envinit(void)
{
	t_env			*env;

	env = (t_env*)malloc(sizeof(t_env));
	env->flag = 0;
	env->start = 1;
	env->norep = 0;
	env->file = 0;
	env->rep = 0;
	return (env);
}
