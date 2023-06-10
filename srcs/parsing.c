/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfresnay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 14:02:26 by lfresnay          #+#    #+#             */
/*   Updated: 2023/06/10 17:18:28 by lfresnay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	ft_initialize_args(t_args *args)
{
	args->l = 0;
	args->R = 0;
	args->a = 0;
	args->r = 0;
	args->t = 0;
	args->nbFiles = 0;
}

int	ft_parse_args(char *arg, t_args *args)
{
	int	i;

	i = 1;
	while (arg[i])
	{
		if (arg[i] == 'l')
			args->l = 1;
		else if (arg[i] == 'R')
			args->R = 1;
		else if (arg[i] == 'a')
			args->a = 1;
		else if (arg[i] == 'r')
			args->r = 1;
		else if (arg[i] == 't')
			args->t = 1;
		else
		{
			ft_printf("ft_ls: illegal option -- %c\n", arg[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

void	ft_add_dir(char *dir_name, t_dir **dirs, char *(*files)[4096], int *j, t_args *args)
{
	t_dir	*new;
	t_dir	*tmp;
	DIR	*dir;

	dir = opendir(dir_name);
	if (dir == NULL)
	{
		args->nbFiles++;
		if (errno == ENOTDIR)
		{
			(*files)[(*j)++] = ft_strdup(dir_name);
			return;
		}
		char	*strtemp = ft_strjoin("ft_ls: ", dir_name);
		perror(strtemp);
		free(strtemp);
		return;
	}
	closedir(dir);
	new = (t_dir *)malloc(sizeof(t_dir));
	new->name = ft_strdup(dir_name);
	new->next = NULL;
	if (*dirs == NULL)
		*dirs = new;
	else
	{
		tmp = *dirs;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	print_only_files(char *files[4096], int j, t_args *args, t_dir **dirs)
{
	int	i = 0;
	t_dir	*cwd_content = NULL;

	while (i < j)
	{
		t_dir	*new_node = malloc(sizeof(t_dir));
		new_node->name = files[i];
		stat(files[i], &(new_node->stats));
		new_node->next = cwd_content;
		cwd_content = new_node;
		i++;
	}
	if (!cwd_content)
		return;
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
	ft_print_content(cwd_content, args, ".", args->nbFiles);
	ft_free_dirs(cwd_content);
	if (j > 0 && ft_size_dirs(*dirs) > 0)
		ft_printf("\n\n");
}

int	ft_parse(int ac, char **av, t_args *args, t_dir **dirs)
{
	int	i;
	int	ret_args;
	char	*files[4096];
	int	j;

	j = 0;
	i = 1;
	ret_args = 0;
	while (i < ac)
	{
		if (av[i][0] == '-')
		{
			ret_args = ft_parse_args(av[i], args);
			if (ret_args == 1)
				return (1);
		}
		else
			ft_add_dir(av[i], dirs, &files, &j, args);
		i++;
	}
	if (ret_args == 1)
	{
		ft_printf("ft_ls: illegal option -- %c\n", av[i][1]);
		ft_printf("usage: ft_ls [-lRart] [file ...]\n");
		return (1);
	}
	if (ft_size_dirs(*dirs) == 0 && args->nbFiles == 0)
		ft_add_dir(".", dirs, &files, &j, args);

	print_only_files(files, j, args, dirs);
	
	return (0);
}
