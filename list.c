/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwells <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/22 17:50:58 by gwells            #+#    #+#             */
/*   Updated: 2015/01/24 12:11:19 by gwells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

char			*modpart(char *droit, t_uint mode)
{
	droit[3] = ((mode & S_IXUSR) ? 'x' : '-');
	droit[3] = (((mode & S_IXUSR) && (mode & S_ISUID)) ? 's' : droit[3]);
	droit[3] = ((!(mode & S_IXUSR) && (mode & S_ISUID)) ? 'S' : droit[3]);
	droit[4] = ((mode & S_IRGRP) ? 'r' : '-');
	droit[5] = ((mode & S_IWGRP) ? 'w' : '-');
	droit[6] = ((mode & S_IXGRP) ? 'x' : '-');
	droit[6] = (((mode & S_IXGRP) && (mode & S_ISGID)) ? 's' : droit[6]);
	droit[6] = ((!(mode & S_IXGRP) && (mode & S_ISGID)) ? 'S' : droit[6]);
	droit[7] = ((mode & S_IROTH) ? 'r' : '-');
	droit[8] = ((mode & S_IWOTH) ? 'w' : '-');
	droit[9] = ((mode & S_IXOTH) ? 'x' : '-');
	droit[9] = (((mode & S_ISVTX) && (mode & S_IXOTH)) ? 't' : droit[9]);
	droit[9] = (((mode & S_ISVTX) && !(mode & S_IXOTH)) ? 'T' : droit[9]);
	droit[10] = '\0';
	return (droit);
}

void			computelist(int ac, char **argv, t_opt *opt)
{
	t_dlist		*norep;
	t_dlist		*lsfile;
	t_dlist		*lsrep;
	t_env		*env;

	env = envinit();
	norep = nrep(ac, argv, env, opt);
	lsfile = isfile(ac, argv, opt, env);
	lsrep = isrep(ac, argv, opt, env);
	print_norep(norep);
	if (!opt->l)
		print_file(lsfile, opt, 1);
	else
		print_l(lsfile, opt, 1);
	if (lsfile->length && lsrep->length)
		ft_putendl("");
	print_rep(lsrep, opt, env);
	ft_dlstdel(&lsfile->head, del2);
	ft_dlstdel(&lsrep->head, del2);
	ft_dlstdel(&norep->head, del);
	free(env);
	free(norep);
	free(lsfile);
	free(lsrep);
}

t_dnode			*createnewnode(char *argv, char *path)
{
	t_value		*value;
	t_dnode		*newnode;
	char		*npath;

	value = (t_value*)malloc(sizeof(t_value));
	value->sb = (struct stat*)malloc(sizeof(struct stat));
	value->argv = (char*)malloc(sizeof(char) * ft_strlen(argv) + 1);
	ft_strcpy(value->argv, argv);
	value->path = ft_strdup(argv);
	if (path)
	{
		ft_strdel(&(value->path));
		if (path[0] == '/' && path[1] == '\0')
			npath = ft_strdup(path);
		else
			npath = ft_strjoin(path, "/");
		value->path = ft_strjoin(npath, argv);
		ft_strdel(&npath);
	}
	if (0 != lstat(value->path, value->sb))
		perror("stat :");
	newnode = ft_dlstnewnode(value, sizeof(t_value));
	free(value);
	return (newnode);
}

static t_dnode	*cpnode(t_dnode *temp)
{
	t_value		*value;
	t_dnode		*newnode;
	t_value		*value2;

	value2 = temp->content;
	value = (t_value*)malloc(sizeof(t_value));
	value->sb = (struct stat*)malloc(sizeof(struct stat));
	value->argv = ft_strdup(value2->argv);
	value->path = ft_strdup(value2->path);
	if (0 != lstat(value->path, value->sb))
		perror("stat :");
	newnode = ft_dlstnewnode(value, sizeof(t_value));
	free(value);
	return (newnode);
}

t_dlist			*create_new_list(t_dlist *lst, int r)
{
	t_dlist		*lsrep;
	t_dnode		*temp;
	t_dnode		*new;
	t_value		*value;
	int			flag;

	temp = (r) ? lst->queue : lst->head;
	lsrep = ft_dlstnew();
	flag = 0;
	while (temp)
	{
		value = temp->content;
		if (S_ISDIR(value->sb->st_mode) && ft_strcmp(value->argv, ".")
				&& ft_strcmp(value->argv, ".."))
		{
			new = cpnode(temp);
			ft_dlstpushback(lsrep, new);
			flag = 1;
		}
		temp = (r) ? temp->prev : temp->next;
	}
	if (!flag)
		free(lsrep);
	return ((flag) ? lsrep : NULL);
}
