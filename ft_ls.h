/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwells <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/17 19:43:46 by gwells            #+#    #+#             */
/*   Updated: 2015/02/07 11:57:44 by gwells           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# define _FILE_OFFSET_BITS 64
# include "libft.h"
# include <dirent.h>
# include <string.h>

typedef unsigned int	t_uint;
typedef	struct passwd	t_passwd;
typedef struct group	t_group;

typedef struct			s_space
{
	int					group;
	int					user;
	int					size;
	int					link;
	int					maj;
	int					min;
	int					flag;
}						t_space;

typedef struct			s_env
{
	int					flag;
	int					start;
	int					norep;
	int					file;
	int					rep;
}						t_env;

typedef struct			s_value
{
	char				*argv;
	char				*path;
	struct stat			*sb;
}						t_value;

typedef struct			s_opt
{
	int					a;
	int					c;
	int					r;
	int					t;
	int					l;
	int					rec;
}						t_opt;

DIR						*ft_open(char *path, int type);
int						isflag(int pos, char **argv);
void					trueflag(char *argv);
char					*flagtochar(char *argv);
char					*doublon(char *argv);
t_dlist					*nrep(int ac, char **argv, t_env *env, t_opt *opt);
void					mallocfail(void);
int						endofflag(int ac, char **argv);
void					ascii_insertion(t_dlist *norep, char *argv, char *path);
t_dlist					*isfile(int ac, char **argv, t_opt *opt, t_env *env);
t_dlist					*isrep(int ac, char **argv, t_opt *opt, t_env *env);
void					computelist(int ac, char **argv, t_opt *opt);
char					*flags(int ac, char **argv);
t_opt					*createopt(char *s);
void					del(void *content, size_t content_size);
void					time_insertion(t_dlist *norep, char *argv, char *path);
void					nrep_insertion(t_dlist *norep, char *argv);
void					del2(void *content, size_t content_size);
int						time_pos(t_dlist *norep, t_dnode *newnode);
int						ascii_pos2(t_dlist *norep, char *argv);
int						ascii_pos(t_dlist *norep, char *argv);
void					print_norep(t_dlist *norep);
void					print_file(t_dlist *lsfile, t_opt *opt, int start);
void					print_rep(t_dlist *lsrep, t_opt *opt, t_env *e);
t_dlist					*ls_temp(DIR *dir, t_opt *opt, char *path);
t_dlist					*create_new_list(t_dlist *lsrep, int r);
void					printlst(t_dlist *toprint);
t_dnode					*createnewnode(char *argv, char *path);
void					print_l(t_dlist *lst, t_opt *opt, int start);
t_dlist					*removeall(t_dlist *lst, char c);
void					print_user(t_dnode *temp, t_space *space);
void					print_lien(char *path);
t_space					*nbr_space(t_dlist *lst);
int						nbr_len(long nbr);
void					space(int space);
void					print_group(t_dnode *temp, t_space *space);
void					total(t_dlist *lst, t_opt *opt);
t_env					*envinit(void);
void					noarg(char *path);
int						statut(char *path, t_opt *opt);
void					putmyenv(t_dlist *lst, t_opt *opt, t_env *env);
char					*modpart(char *droit, t_uint mode);
char					*openable_path(char *path, char *name);
#endif
