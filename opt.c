/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwells <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/25 21:02:27 by gwells            #+#    #+#             */
/*   Updated: 2015/01/24 11:55:02 by gwells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdlib.h>

static void	initalize(t_opt *opt)
{
	opt->a = 0;
	opt->r = 0;
	opt->t = 0;
	opt->l = 0;
	opt->rec = 0;
	opt->c = 0;
}

char		*flags(int ac, char **argv)
{
	int		end;
	int		i;

	i = 1;
	end = endofflag(ac, argv);
	if (!ft_strcmp(argv[end - 1], "--"))
		end--;
	while (i != end)
	{
		trueflag(argv[i]);
		i++;
	}
	return (flagtochar(NULL));
}

t_opt		*createopt(char *s)
{
	t_opt	*opt;

	opt = (t_opt*)malloc(sizeof(t_opt));
	initalize(opt);
	if (s)
	{
		while (*s)
		{
			if (*s == 'a')
				opt->a = 1;
			else if (*s == 'r')
				opt->r = 1;
			else if (*s == 't')
				opt->t = 1;
			else if (*s == 'l')
				opt->l = 1;
			else if (*s == '1')
				opt->c = 1;
			else if (*s == 'R')
				opt->rec = 1;
			s++;
		}
	}
	return (opt);
}

void		putmyenv(t_dlist *newlst, t_opt *opt, t_env *env)
{
	if (opt->rec && newlst)
	{
		env->start = 0;
		env->flag = 1;
		print_rep(newlst, opt, env);
	}
	if (newlst)
	{
		ft_dlstdel(&newlst->head, del2);
		free(newlst);
	}
}
