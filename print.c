/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwells <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/02 19:21:48 by gwells            #+#    #+#             */
/*   Updated: 2015/02/07 10:31:04 by gwells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdlib.h>
#include <sys/stat.h>

void			print_norep(t_dlist *norep)
{
	t_dnode		*temp;

	temp = norep->head;
	while (temp)
	{
		ft_open(temp->content, 1);
		temp = temp->next;
	}
}

void			print_file(t_dlist *lsfile, t_opt *opt, int start)
{
	t_dnode		*temp;
	t_value		*value;

	temp = (opt->r) ? lsfile->queue : lsfile->head;
	while (temp)
	{
		value = temp->content;
		while (temp && value->argv[0] == '.')
		{
			if (opt->a || start)
				ft_putendl(value->argv);
			temp = (opt->r) ? temp->prev : temp->next;
			if (temp)
				value = temp->content;
		}
		if (temp)
		{
			ft_putendl(value->argv);
			temp = (opt->r) ? temp->prev : temp->next;
		}
	}
}

static void		norme(DIR *folder, t_opt *opt, t_dnode *temp, t_env *env)
{
	t_dlist		*lst;
	t_value		*value;
	t_dlist		*newlst;

	value = temp->content;
	if ((lst = ls_temp(folder, opt, value->path))
		&& (!ft_strcmp(value->argv, ".")
		|| ((value->argv[0] != '.') || opt->a || env->start)))
	{
		if (!opt->l)
			print_file(lst, opt, 0);
		else
			print_l(lst, opt, 0);
	}
	closedir(folder);
	newlst = create_new_list(lst, opt->r);
	ft_dlstdel(&lst->head, del2);
	free(lst);
	putmyenv(newlst, opt, env);
}

void			print_rep(t_dlist *lsrep, t_opt *opt, t_env *e)
{
	t_dnode		*temp;
	t_value		*value;
	DIR			*folder;

	temp = (opt->r && e->start) ? lsrep->queue : lsrep->head;
	while (temp)
	{
		value = temp->content;
		if ((e->flag && (value->argv[0] != '.' || opt->a))
		|| (e->start && (lsrep->length > 1
		|| ((e->file || e->norep) && e->rep))))
		{
			if (e->flag)
				ft_putchar('\n');
			ft_putstr(value->path);
			ft_putendl(":");
		}
		folder = ft_open(value->path, 0);
		if (folder)
		{
			norme(folder, opt, temp, e);
			e->flag = 1;
		}
		temp = (opt->r && e->start) ? temp->prev : temp->next;
	}
}

void			total(t_dlist *lst, t_opt *opt)
{
	t_dnode		*temp;
	t_value		*value;
	int			size;

	temp = lst->head;
	size = 0;
	while (temp)
	{
		value = temp->content;
		if (opt->a || value->argv[0] != '.')
			size += (int)value->sb->st_blocks;
		temp = temp->next;
	}
	ft_putstr("total ");
	ft_putnbr(size);
	ft_putendl("");
}
