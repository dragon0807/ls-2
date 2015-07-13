/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_l3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwells <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/17 12:44:07 by gwells            #+#    #+#             */
/*   Updated: 2015/01/25 07:14:15 by gwells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <grp.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

static void		ls_size(t_dnode *temp, t_space *sp)
{
	t_value		*value;

	value = temp->content;
	if (S_ISCHR(value->sb->st_mode) || S_ISBLK(value->sb->st_mode))
	{
		space(sp->maj - nbr_len(major(value->sb->st_rdev)));
		ft_putnbr(major(value->sb->st_rdev));
		ft_putstr(", ");
		space(sp->min - nbr_len(minor(value->sb->st_rdev)));
		ft_putnbr(minor(value->sb->st_rdev));
		sp->flag = 1;
	}
	else
	{
		if (sp->flag)
			space(sp->size - nbr_len(value->sb->st_size) + sp->maj + sp->min);
		else
			space(sp->size - nbr_len(value->sb->st_size));
		ft_putnbr(value->sb->st_size);
	}
}

void			print_group(t_dnode *temp, t_space *sp)
{
	t_group		*group;
	t_value		*value;

	value = temp->content;
	group = getgrgid(value->sb->st_gid);
	if (group)
	{
		ft_putstr(group->gr_name);
		space(sp->group - ft_strlen(group->gr_name));
	}
	else
	{
		ft_putnbr(value->sb->st_gid);
		space(sp->group - nbr_len(value->sb->st_gid));
	}
	ft_putstr("  ");
	ls_size(temp, sp);
}

void			print_lien(char *path)
{
	char		*buf;
	int			i;
	int			r;

	i = 0;
	r = 0;
	while (r == i)
	{
		buf = ft_strnew(++i);
		r = readlink(path, buf, i);
		if (r == -1)
			ft_putstr(strerror(errno));
		if (r == i)
			free(buf);
	}
	ft_putstr(" -> ");
	ft_putstr(buf);
	free(buf);
}

static int		norme(struct stat *s)
{
	if (S_ISLNK(s->st_mode))
		return (-1);
	else if (S_ISDIR(s->st_mode))
		return (0);
	else
		return (-1);
}

int				statut(char *path, t_opt *opt)
{
	struct stat	s;
	int			t;
	char		*buf;

	if (!opt->l)
		t = stat(path, &s);
	else
		t = lstat(path, &s);
	buf = malloc(sizeof(char) * 10);
	noarg(path);
	if ((errno == ENOENT || errno == ENOTDIR) && t == -1)
	{
		if (readlink(path, buf, 10) == -1)
			return (1);
		else
			return (-1);
	}
	free(buf);
	return (norme(&s));
}
