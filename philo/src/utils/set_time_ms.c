/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_time_ms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 14:07:13 by mgo               #+#    #+#             */
/*   Updated: 2022/03/26 13:06:28 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>

int	set_time_ms(long int *dest)
{
	long int		ret;
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	ret = (tv.tv_sec * 1000);
	ret += (tv.tv_usec / 1000);
	*dest = ret;
	return (0);
}
