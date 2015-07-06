/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insertion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwells <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/07 23:05:40 by gwells            #+#    #+#             */
/*   Updated: 2015/02/07 11:35:15 by gwells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			nrep_insertion(t_dlist *norep, char *argv)
{
	t_dnode		*newnode;

	newnode = ft_dlstnewnode(argv, ft_strlen(argv) + 1);
	norep = ft_dlstinsert(norep, newnode, ascii_pos2(norep, argv));
}

void			ascii_insertion(t_dlist *norep, char *argv, char *path)
{
	t_dnode		*newnode;

	newnode = createnewnode(argv, path);
	norep = ft_dlstinsert(norep, newnode, ascii_pos(norep, argv));
}

void			time_insertion(t_dlist *norep, char *argv, char *path)
{
	t_dnode		*newnode;

	newnode = createnewnode(argv, path);
	norep = ft_dlstinsert(norep, newnode, time_pos(norep, newnode));
}
