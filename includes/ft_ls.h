/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfresnay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 14:02:20 by lfresnay          #+#    #+#             */
/*   Updated: 2023/06/10 15:57:08 by lfresnay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
# include <dirent.h>
# include <errno.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>

typedef struct	s_args
{
	int			l;
	int			R;
	int			a;
	int			r;
	int			t;
	int			nbFiles;
}				t_args;

typedef struct	s_dir
{
	char			*name;
	struct stat		stats;
	struct s_dir	*next;
}				t_dir;

/* MAIN */
void	ft_execute_ls(t_args *args, t_dir *dirs);
void	list_files(char *dir_name, t_args *args, int hasNext);

/* PARSING */
void	ft_initialize_args(t_args *args);
int		ft_parse_args(char *arg, t_args *args);
void	ft_add_dir(char *dir_name, t_dir **dirs, char *(*files)[4096], int *j, t_args *args);
int		ft_parse(int ac, char **av, t_args *args, t_dir **dirs);

/* TOOLS */
void	ft_free_dirs(t_dir *dirs);
int		ft_size_dirs(t_dir *dirs);
void	swap_nodes(t_dir **dirs, t_dir *node1, t_dir *node2);

/* SORTING */
void	ft_rev_alphabetical_order(t_dir **dirs);
void	ft_alphabetical_order(t_dir **dirs);
void	ft_time_order(t_dir **dirs);
void	ft_rev_time_order(t_dir **dirs);

/* PRINT */
void	ft_print_content(t_dir *dirs, t_args *args, char *actualPath, int isFiles);
void	print_time(struct stat file_stat);
void	print_file_permissions(struct stat file_stat);
int		getDirs(t_dir *dirs, t_args *args, char *actualPath, char *(*recursive_dirs)[4096]);

#endif
