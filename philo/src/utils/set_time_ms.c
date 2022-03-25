/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_time_ms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 14:07:13 by mgo               #+#    #+#             */
/*   Updated: 2022/03/25 16:20:34 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>

long int	set_time_ms(long int *dest)
{
	long int		ret;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	ret = (tv.tv_sec * 1000);
	ret += (tv.tv_usec / 1000);
	*dest = ret;
	return (ret);
}
