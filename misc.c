/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwells <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/07 22:52:07 by gwells            #+#    #+#             */
/*   Updated: 2015/01/27 14:12:26 by gwells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdlib.h>
#include <sys/stat.h>

void				mallocfail(void)
{
	ft_putendl("malloc() failed");
	exit(EXIT_FAILURE);
}

void				del(void *content, size_t content_size)
{
	free(content);
	content_size++;
	content_size--;
}

void				del2(void *content, size_t content_size)
{
	t_value			*temp;

	temp = content;
	free(temp->argv);
	free(temp->path);
	free(temp->sb);
	free(temp);
	content_size++;
	content_size--;
}

static t_dlist		*remove_head_queue(t_dlist *lst, t_dnode *temp)
{
	if (temp->next == NULL && temp->prev == NULL)
	{
		lst->head = NULL;
		lst->queue = NULL;
	}
	else if (temp->next == NULL)
	{
		lst->queue = temp->prev;
		lst->queue->next = NULL;
	}
	else
	{
		lst->head = temp->next;
		lst->head->prev = NULL;
	}
	return (lst);
}

t_dlist				*removeall(t_dlist *lst, char c)
{
	t_dnode			*temp;
	t_dnode			*del;

	temp = lst->head;
	while (temp)
	{
		if (((t_value*)(temp->content))->argv[0] == c)
		{
			del = temp;
			temp = temp->next;
			if (!del->next || !del->prev)
				lst = remove_head_queue(lst, del);
			else
			{
				del->prev->next = del->next;
				del->next->prev = del->prev;
			}
			ft_dlstdelone(&del, del2);
			lst->length--;
		}
		else
			temp = temp->next;
	}
	return (lst);
}
