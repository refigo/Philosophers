/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mgo_calloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 16:50:03 by mgo               #+#    #+#             */
/*   Updated: 2022/02/24 17:01:58 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*mgo_calloc(void **dest, size_t count, size_t size)
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
	if (!allocated)
		return (FALSE);
	*dest = (void *)allocated;
	return (TRUE);
}

