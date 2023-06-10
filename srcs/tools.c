/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfresnay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 14:03:07 by lfresnay          #+#    #+#             */
/*   Updated: 2023/06/10 14:03:08 by lfresnay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int	ft_size_dirs(t_dir *dirs)
{
	int		i;
	t_dir	*tmp;

	i = 0;
	tmp = dirs;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void	ft_free_dirs(t_dir *dirs)
{
	t_dir *tmp;

	while (dirs != NULL)
	{
		tmp = dirs;
		dirs = dirs->next;
		free(tmp->name);
		free(tmp);
	}
}

void swap_nodes(t_dir **dirs, t_dir *node1, t_dir *node2)
{
	t_dir *prev_node1 = NULL;
	t_dir *prev_node2 = NULL;
	t_dir *tmp;

	if (node1 == node2)
		return;

	tmp = *dirs;
	while (tmp != NULL)
	{
		if (tmp->next == node1)
			prev_node1 = tmp;
		else if (tmp->next == node2)
			prev_node2 = tmp;
		tmp = tmp->next;
	}

	if (prev_node1 != NULL)
		prev_node1->next = node2;
	else
		*dirs = node2;

	if (prev_node2 != NULL)
		prev_node2->next = node1;
	else
		*dirs = node1;

	tmp = node1->next;
	node1->next = node2->next;
	node2->next = tmp;
}
