/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwells <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/28 16:00:02 by gwells            #+#    #+#             */
/*   Updated: 2015/02/07 12:03:17 by gwells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int					g_ret = 0;

static void			ft_open_fail(char *path)
{
	char			*str;

	if (!ft_strrchr(path, '/'))
	{
		str = ft_strjoin("ft_ls: ", path);
		perror(str);
	}
	else
	{
		str = ft_strjoin("ft_ls: ", ft_strrchr(path, '/') + 1);
		perror(str);
	}
	free(str);
	g_ret = 1;
}

DIR					*ft_open(char *path, int type)
{
	DIR				*rep;
	char			*str;

	rep = opendir(path);
	if (!rep && type)
	{
		str = ft_strjoin("ft_ls: ", path);
		perror(str);
		free(str);
		g_ret = 1;
	}
	if (!rep && !type)
		ft_open_fail(path);
	return (rep);
}

t_dlist				*ls_temp(DIR *dir, t_opt *opt, char *path)
{
	struct dirent	*file;
	t_dlist			*lst;
	struct stat 	s;
	char		 	*o_path;

	file = NULL;
	lst = ft_dlstnew();
	while ((file = readdir(dir)) != NULL)
	{
		o_path = openable_path(path, file->d_name);
		if (!stat(o_path, &s))
		{
			if (!opt->t)
				ascii_insertion(lst, file->d_name, path);
			else
				time_insertion(lst, file->d_name, path);
		}
		else 
			ft_open_fail(o_path);	
		free(o_path);
	}
	return (lst);
}

char				*openable_path(char *path, char *name)
{
	char 			*temp;
	char			*o_path;

	temp = ft_strjoin(path, "/");
	o_path = ft_strjoin(temp, name);
	free(temp);
	return (o_path);
}

int					main(int ac, char **argv)
{
	char			*s;
	char			*s2;
	t_opt			*opt;

	s = flags(ac, argv);
	s2 = ft_union(s);
	ft_strdel(&s);
	opt = createopt(s2);
	ft_strdel(&s2);
	computelist(ac, argv, opt);
	free(opt);
	return (g_ret);
}
