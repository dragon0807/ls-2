/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_l.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwells <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/17 12:33:48 by gwells            #+#    #+#             */
/*   Updated: 2015/02/07 12:23:21 by gwells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <sys/stat.h>
#include <stdlib.h>
#include <time.h>

static void		mod(t_dnode *temp)
{
	char		*droit;
	t_uint		mode;

	if (!(droit = (char *)malloc(sizeof(char) * (11))))
		mallocfail();
	mode = (((t_value*)(temp->content))->sb->st_mode);
	droit[0] = (S_ISSOCK(mode) ? 's' : '-');
	droit[0] = (S_ISLNK(mode) ? 'l' : droit[0]);
	droit[0] = (S_ISREG(mode) ? '-' : droit[0]);
	droit[0] = (S_ISBLK(mode) ? 'b' : droit[0]);
	droit[0] = (S_ISDIR(mode) ? 'd' : droit[0]);
	droit[0] = (S_ISCHR(mode) ? 'c' : droit[0]);
	droit[0] = (S_ISFIFO(mode) ? 'p' : droit[0]);
	droit[1] = ((mode & S_IRUSR) ? 'r' : '-');
	droit[2] = ((mode & S_IWUSR) ? 'w' : '-');
	droit = modpart(droit, mode);
	ft_putstr(droit);
	ft_strdel(&droit);
	space(2);
}

void			space(int space)
{
	while (space-- != 0)
		ft_putstr(" ");
}

static int		six_months(t_dnode *temp)
{
	t_value		*value;

	value = temp->content;
	if (value->sb->st_mtime <= (time(NULL) - 15778463)
		|| value->sb->st_mtime > time(NULL))
		return (1);
	else
		return (0);
}

static void		print_date(t_dnode *temp)
{
	char		*str;
	char		*date;
	t_value		*value;

	value = temp->content;
	date = ctime(&(value->sb->st_mtime));
	ft_putstr(" ");
	if (six_months(temp))
	{
		str = ft_strsub(date, 4, 7);
		ft_putstr(str);
		ft_strdel(&str);
		str = ft_strsub(date, 19, 5);
		ft_putstr(str);
		ft_strdel(&str);
	}
	else
	{
		str = ft_strsub(date, 4, 12);
		ft_putstr(str);
		ft_strdel(&str);
	}
	space(1);
}

void			print_l(t_dlist *lst, t_opt *opt, int start)
{
	t_dnode		*temp;
	t_space		*sp;

		if (!opt->a)
		lst = removeall(lst, '.');
		if (!start && lst->length > 0)
		total(lst, opt);

	temp = (opt->r) ? lst->queue : lst->head;
	sp = nbr_space(lst);
	while (temp)
	{
		mod(temp);
		space(sp->link - nbr_len(((t_value*)(temp->content))->sb->st_nlink));
		ft_putnbr(((t_value*)(temp->content))->sb->st_nlink);
		space(1);
		print_user(temp, sp);
		print_date(temp);
		ft_putstr(((t_value*)(temp->content))->argv);
		if (S_ISLNK(((t_value*)(temp->content))->sb->st_mode))
			print_lien(((t_value*)(temp->content))->path);
		ft_putendl("");
		temp = (opt->r) ? temp->prev : temp->next;
	}
	free(sp);
}
