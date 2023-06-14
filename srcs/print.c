/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfresnay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 14:01:59 by lfresnay          #+#    #+#             */
/*   Updated: 2023/06/14 10:10:45 by lfresnay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void print_file_permissions(struct stat file_stat)
{
	if (S_ISLNK(file_stat.st_mode))
		ft_printf("l");
	else if (S_ISDIR(file_stat.st_mode))
		ft_printf("d");
	else
		ft_printf("-");
	ft_printf((file_stat.st_mode & S_IRUSR) ? "r" : "-");
	ft_printf((file_stat.st_mode & S_IWUSR) ? "w" : "-");
	ft_printf((file_stat.st_mode & S_IXUSR) ? "x" : "-");
	ft_printf((file_stat.st_mode & S_IRGRP) ? "r" : "-");
	ft_printf((file_stat.st_mode & S_IWGRP) ? "w" : "-");
	ft_printf((file_stat.st_mode & S_IXGRP) ? "x" : "-");
	ft_printf((file_stat.st_mode & S_IROTH) ? "r" : "-");
	ft_printf((file_stat.st_mode & S_IWOTH) ? "w" : "-");
	ft_printf((file_stat.st_mode & S_IXOTH) ? "x" : "-");
	ft_printf(" ");
}

void print_time(struct stat file_stat)
{
	char buffer[80];
	struct tm *timeinfo;

	timeinfo = localtime(&file_stat.st_mtime);
	strftime(buffer, sizeof(buffer), "%b %d %H:%M", timeinfo);
	ft_printf("%s ", buffer);
}

int ft_size_content(t_dir *dirs, t_args *args)
{
	t_dir	*tmp;
	int		i;

	i = 0;
	tmp = dirs;
	while (tmp)
	{
		if (S_ISDIR(tmp->stats.st_mode))
		{
			tmp = tmp->next;
			continue ;
		}
		if (args->a == 1)
		{
			if (tmp->stats.st_size % 4096 != 0)
				i += (tmp->stats.st_size / 4096) * 8 + 8;
			else
				i += (tmp->stats.st_size / 4096) * 8;
		}
		else if (tmp->name[0] != '.')
		{
			if (tmp->stats.st_size % 4096 != 0)
				i += (tmp->stats.st_size / 4096) * 8 + 8;
			else
				i += (tmp->stats.st_size / 4096) * 8;
		}
		tmp = tmp->next;
	}
	return (i);
}

void	ft_print_file(t_dir *tmp, t_args *args, int *nbFiles, char *actualPath)
{
	if (args->l == 1 && args->a == 1)
	{
		print_file_permissions(tmp->stats);
		ft_printf("%-2d ", tmp->stats.st_nlink);
		ft_printf("%-12s ", getpwuid(tmp->stats.st_uid)->pw_name);
		ft_printf("%-12s ", getgrgid(tmp->stats.st_gid)->gr_name);
		ft_printf("%10d ", tmp->stats.st_size);
		print_time(tmp->stats);
		ft_printf("%s", tmp->name);
		if (S_ISLNK(tmp->stats.st_mode))
		{
			char buf[1024];
			int len;

			if ((len = readlink(tmp->name, buf, sizeof(buf) - 1)) != -1)
			{
				buf[len] = '\0';
				ft_printf(" -> %s", buf);
			}
		}
		(*nbFiles)++;
	}
	else if (args->l == 1 && tmp->name[0] != '.')
	{
		print_file_permissions(tmp->stats);
		ft_printf("%-2d ", tmp->stats.st_nlink);
		ft_printf("%-12s ", getpwuid(tmp->stats.st_uid)->pw_name);
		ft_printf("%-12s ", getgrgid(tmp->stats.st_gid)->gr_name);
		ft_printf("%10d ", tmp->stats.st_size);
		print_time(tmp->stats);
		ft_printf("%s", tmp->name);
		if (S_ISLNK(tmp->stats.st_mode))
		{
			char buf[1024];
			int len;

			char	*temp = ft_strjoin(actualPath, "/");
			char	*path = ft_strjoin(temp, tmp->name);
			free(temp);
			if ((len = readlink(path, buf, sizeof(buf) - 1)) != -1)
			{
				buf[len] = '\0';
				ft_printf(" -> %s", buf);
			}
			free(path);
		}
		(*nbFiles)++;
	}
	if (args->a == 1 && args->l == 0)
	{
		ft_printf("%s", tmp->name);
		(*nbFiles)++;
	}
	else if (tmp->name[0] != '.' && args->l == 0)
	{
		ft_printf("%s", tmp->name);
		(*nbFiles)++;
	}
	if (args->l == 1 && tmp->next != NULL)
	{
		if (args->a == 1)
			ft_printf("\n");
		else if (tmp->name && tmp->name[0] != '.')
			ft_printf("\n");
	}
	else if (args->l == 0 && tmp->next != NULL && !(args->a == 0 && tmp->name[0] == '.'))
		ft_printf("  ");
}

int	getDirs(t_dir *dirs, t_args *args, char *actualPath, char *(*recursive_dirs)[4096])
{
	t_dir	*tmp;
	int		i = 0;

	tmp = dirs;
	while (tmp)
	{
		if ((S_ISDIR(tmp->stats.st_mode) && args->R == 1) && !(tmp->name[0] == '.' && tmp->name[1] == '.') && !(tmp->name[0] == '.' && ft_strlen(tmp->name) == 1))
		{
			char	*tmpPath = ft_strjoin(actualPath, "/");
			(*recursive_dirs)[i++] = ft_strjoin(tmpPath, tmp->name);
			free(tmpPath);
		}
		tmp = tmp->next;
	}
	return (i);
}

void ft_print_content(t_dir *dirs, t_args *args, char *actualPath, int isFiles)
{
	t_dir *tmp;
	char	*recursive_dirs[4096];
	int		i;
	int		nbFiles = 0;

	tmp = dirs;
	i = getDirs(dirs, args, actualPath, &recursive_dirs);
	if (args->l == 1 && isFiles == 0)
		ft_printf("total %d\n", ft_size_content(dirs, args));
	while (tmp)
	{
		ft_print_file(tmp, args, &nbFiles, actualPath);
		tmp = tmp->next;
	}
	if (isFiles == 1)
		ft_printf("\n");

	if (nbFiles > 0 || i > 0)
		ft_printf("\n");

	if (i > 0)
		ft_printf("\n");

	for (int j = 0; j < i; j++)
	{
		if (ft_strnstr(recursive_dirs[j], "/.", ft_strlen(recursive_dirs[j])) != NULL && args->a == 0)
		{
			free(recursive_dirs[j]);
			continue ;
		}
		if (ft_strncmp(recursive_dirs[j], "./.", 4) == 0 && ft_strncmp(recursive_dirs[j], "./..", 5) == 0)
		{
			free(recursive_dirs[j]);
			continue ;
		}
		ft_printf("%s:\n", recursive_dirs[j]);
		list_files(recursive_dirs[j], args, i - 1 != j);
		free(recursive_dirs[j]);
	}
}
