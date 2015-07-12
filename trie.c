/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trie.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwells <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/01 22:02:11 by gwells            #+#    #+#             */
/*   Updated: 2015/01/27 14:11:23 by gwells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <sys/stat.h>

static void		norme(t_dnode **temp, t_value **oldvalue)
{
	*temp = (*temp)->next;
	if (*temp)
		*oldvalue = (*temp)->content;
}

static int		boucle(t_dnode *temp, int count, t_value *nv, t_value *ov)
{
	while (temp)
	{
		while (temp && nv->sb->st_mtime < ov->sb->st_mtime)
		{
			count++;
			norme(&temp, &ov);
		}
		while (temp && nv->sb->st_mtime == ov->sb->st_mtime)
		{
			if (ft_strcmp(ov->argv, nv->argv) <= 0)
				count++;
			else
				return (count);
			norme(&temp, &ov);
		}
		while (temp && nv->sb->st_mtime > ov->sb->st_mtime)
			norme(&temp, &ov);
	}
	return (count);
}

int				time_pos(t_dlist *norep, t_dnode *newnode)
{
	int			count;
	t_dnode		*temp;
	t_value		*newvalue;
	t_value		*oldvalue;

	count = 0;
	temp = norep->head;
	newvalue = newnode->content;
	if (temp)
		oldvalue = temp->content;
	return (boucle(temp, count, newvalue, oldvalue));
}

int				ascii_pos2(t_dlist *norep, char *argv)
{
	int			count;
	t_dnode		*temp;

	count = 0;
	temp = norep->head;
	while (temp != NULL && ft_strcmp(temp->content, argv) <= 0)
	{
		count++;
		temp = temp->next;
	}
	return (count);
}

int				ascii_pos(t_dlist *norep, char *argv)
{
	int			count;
	t_dnode		*temp;
	t_value		*value;

	count = 0;
	temp = norep->head;
	if (temp)
		value = temp->content;
	while (temp != NULL && ft_strcmp(value->argv, argv) <= 0)
	{
		count++;
		temp = temp->next;
		if (temp != NULL)
			value = temp->content;
	}
	return (count);
}
