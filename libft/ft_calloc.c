/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfresnay <lfresnay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 11:04:57 by lfresnay          #+#    #+#             */
/*   Updated: 2022/11/09 10:43:11 by lfresnay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*result;
	size_t	size_t_max;

	size_t_max = 4294967295;
	if (size > size_t_max || count > size_t_max || count * size > size_t_max)
		return (0);
	result = (void *) malloc(size * count);
	if (!result)
		return (0);
	ft_bzero(result, count * size);
	return (result);
}
