/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mgo_calloc_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 09:37:37 by mgo               #+#    #+#             */
/*   Updated: 2022/04/06 09:40:26 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*mgo_calloc(size_t count, size_t size)
{
	char			*allocated;
	unsigned int	i;

	allocated = (char *)malloc(count * size);
	if (!allocated)
		return (NULL);
	i = 0;
	while (i < (count * size))
	{
		allocated[i] = 0;
		i++;
	}
	return ((void *)allocated);
}
