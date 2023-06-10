/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfresnay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 14:02:07 by lfresnay          #+#    #+#             */
/*   Updated: 2023/06/10 16:55:44 by lfresnay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	list_files(char *dir_name, t_args *args, int hasNext)
{
	struct dirent	*entry;
	DIR				*dir;
	t_dir			*cwd_content;
	char			*path;
	char			*tmp;

	cwd_content = NULL;
	dir = opendir(dir_name);
	if (dir == NULL)
	{
		perror("Unable to read directory");
		return;
	}
	while ((entry = readdir(dir)) != NULL)
	{
		t_dir	*new_node = malloc(sizeof(t_dir));
		new_node->name = ft_strdup(entry->d_name);
		tmp = ft_strjoin(dir_name, "/");
		path = ft_strjoin(tmp, new_node->name);
		free(tmp);
		stat(path, &(new_node->stats));
		free(path);
		new_node->next = cwd_content;
		cwd_content = new_node;
	}
	closedir(dir);

	if (args->t == 1)
	{
		if (args->r == 0)
			ft_time_order(&cwd_content);
		else
			ft_rev_time_order(&cwd_content);
	}
	else
	{
		if (args->r == 0)
			ft_alphabetical_order(&cwd_content);
		else
			ft_rev_alphabetical_order(&cwd_content);
	}
	ft_print_content(cwd_content, args, dir_name, 0);
	if (hasNext)
		ft_printf("\n");
	ft_free_dirs(cwd_content);
}

void	ft_execute_ls(t_args *args, t_dir *dirs)
{
	t_dir	*tmp;
	char	*recursive_dirs[4096];
	int	nbDirs;

	tmp = dirs;
	while (tmp)
	{
		nbDirs = getDirs(dirs, args, tmp->name, &recursive_dirs);
		if (ft_size_dirs(dirs) > 1 || (args->R == 1 && nbDirs > 0) || args->nbFiles > 0)
			ft_printf("%s:\n", tmp->name);
		list_files(tmp->name, args, tmp->next != NULL);
		tmp = tmp->next;
	}
}

int main(int argc, char *argv[])
{
	int		ret_args;
	t_args	*args;
	t_dir	*dirs;

	ret_args = 0;
	dirs = NULL;
	args = malloc(sizeof(t_args));
	ft_initialize_args(args);
	ret_args = ft_parse(argc, argv, args, &dirs);
	if (ret_args == 1)
	{
		free(args);
		ft_free_dirs(dirs);
		exit (1);
	}
	else
	{
		ft_execute_ls(args, dirs);
	}
	free(args);
	ft_free_dirs(dirs);
	return 0;
}
