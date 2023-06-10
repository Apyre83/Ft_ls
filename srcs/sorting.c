/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfresnay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 14:02:58 by lfresnay          #+#    #+#             */
/*   Updated: 2023/06/10 14:02:59 by lfresnay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void ft_alphabetical_order(t_dir **dirs)
{
	t_dir *current;
	t_dir *next;
	int swapped;

	if (*dirs == NULL)
		return;

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		current = *dirs;
		while (current->next != NULL)
		{
			next = current->next;
			if (ft_strncmp(current->name, next->name, ft_strlen(current->name)) > 0)
			{
				swap_nodes(dirs, current, next);
				swapped = 1;
			}
			else
			{
				current = current->next;
			}
		}
	}
}

void ft_rev_alphabetical_order(t_dir **dirs)
{
	t_dir *current;
	t_dir *next;
	int swapped;

	if (*dirs == NULL)
		return;

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		current = *dirs;
		while (current->next != NULL)
		{
			next = current->next;
			if (ft_strncmp(current->name, next->name, ft_strlen(current->name)) < 0)
			{
				swap_nodes(dirs, current, next);
				swapped = 1;
			}
			else
			{
				current = current->next;
			}
		}
	}
}

void	ft_time_order(t_dir **dirs)
{
	t_dir *current;
	t_dir *next;
	int swapped;

	if (*dirs == NULL)
		return;

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		current = *dirs;
		while (current->next != NULL)
		{
			next = current->next;
			if (current->stats.st_mtime < next->stats.st_mtime)
			{
				swap_nodes(dirs, current, next);
				swapped = 1;
			}
			else if (current->stats.st_mtime == next->stats.st_mtime)
			{
				if (ft_strncmp(current->name, next->name, ft_strlen(current->name)) > 0)
				{
					swap_nodes(dirs, current, next);
					swapped = 1;
				}
				else
					current = current->next;
			}
			else
				current = current->next;
		}
	}
}


void	ft_rev_time_order(t_dir **dirs)
{
	t_dir *current;
	t_dir *next;
	int swapped;

	if (*dirs == NULL)
		return;

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		current = *dirs;
		while (current->next != NULL)
		{
			next = current->next;
			if (current->stats.st_mtime > next->stats.st_mtime)
			{
				swap_nodes(dirs, current, next);
				swapped = 1;
			}
			else if (current->stats.st_mtime == next->stats.st_mtime)
			{
				if (ft_strncmp(current->name, next->name, ft_strlen(current->name)) < 0)
				{
					swap_nodes(dirs, current, next);
					swapped = 1;
				}
				else
					current = current->next;
			}
			else
				current = current->next;
		}
	}
}
