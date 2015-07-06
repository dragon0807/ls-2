/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_l2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwells <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/17 12:41:08 by gwells            #+#    #+#             */
/*   Updated: 2015/01/24 07:39:54 by gwells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <grp.h>
#include <pwd.h>

static t_space		*space_init(void)
{
	t_space			*space;

	space = (t_space*)malloc(sizeof(t_space));
	space->link = 0;
	space->size = 0;
	space->user = 0;
	space->group = 0;
	space->min = 0;
	space->maj = 0;
	space->flag = 0;
	return (space);
}

int					nbr_len(long nbr)
{
	int				i;

	i = 1;
	while (nbr /= 10)
		i++;
	return (i);
}

static void			nbr_space2(t_dnode *temp, t_space *space)
{
	int				group;
	int				user;
	int				min;
	struct group	*sgroup;
	struct passwd	*suser;

	sgroup = getgrgid(((t_value*)(temp->content))->sb->st_gid);
	suser = getpwuid(((t_value*)(temp->content))->sb->st_uid);
	if (sgroup)
		group = ft_strlen(sgroup->gr_name);
	else
		group = nbr_len(((t_value*)(temp->content))->sb->st_gid);
	if (suser)
		user = ft_strlen(suser->pw_name);
	else
		user = nbr_len(((t_value*)(temp->content))->sb->st_uid);
	min = nbr_len(minor(((t_value*)(temp->content))->sb->st_rdev));
	space->group = (space->group < group) ? group : space->group;
	space->user = (space->user < user) ? user : space->user;
	space->min = (space->min < min) ? min : space->min;
}

t_space				*nbr_space(t_dlist *lst)
{
	t_space			*space;
	t_dnode			*temp;
	int				nlink;
	int				size;
	int				maj;

	space = space_init();
	temp = lst->head;
	while (temp)
	{
		nbr_space2(temp, space);
		nlink = nbr_len(((t_value*)(temp->content))->sb->st_nlink);
		size = nbr_len(((t_value*)(temp->content))->sb->st_size);
		maj = nbr_len(major(((t_value*)(temp->content))->sb->st_rdev)) + 1;
		space->link = (space->link < nlink) ? nlink : space->link;
		space->size = (space->size < size) ? size : space->size;
		space->maj = (space->maj < maj) ? maj : space->maj;
		temp = temp->next;
	}
	return (space);
}

void				print_user(t_dnode *temp, t_space *sp)
{
	t_passwd		*user;
	t_value			*value;

	value = temp->content;
	user = getpwuid(value->sb->st_uid);
	if (user)
	{
		ft_putstr(user->pw_name);
		space(sp->user - ft_strlen(user->pw_name));
	}
	else
	{
		ft_putnbr(value->sb->st_uid);
		space(sp->user - nbr_len(value->sb->st_uid));
	}
	ft_putstr("  ");
	print_group(temp, sp);
}
