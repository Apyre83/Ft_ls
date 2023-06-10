/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfresnay <lfresnay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 11:17:19 by lfresnay          #+#    #+#             */
/*   Updated: 2022/11/08 17:38:45 by lfresnay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*result;

	result = malloc((ft_strlen((char *) s) + 1) * sizeof(char));
	if (!result)
		return (0);
	(void) ft_strlcpy(result, s, ft_strlen((char *) s) + 1);
	return (result);
}
