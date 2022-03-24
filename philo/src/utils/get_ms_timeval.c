/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ms_timeval.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 13:21:39 by mgo               #+#    #+#             */
/*   Updated: 2022/03/24 12:03:26 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>

/*
long long	get_ms_timeval(struct timeval tv)
{
	long long	ret;

	ret = (tv.tv_sec * 1000);
	ret += (tv.tv_usec / 1000);
	return (ret);
}

long int	get_time_ms(void)
{
	long int		ret;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	ret = (tv.tv_sec * 1000);
	ret += (tv.tv_usec / 1000);
	return (ret);
}
*/

long int	set_time_ms(long int *dest)
{
	long int		ret;
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (FAIL);
	ret = (tv.tv_sec * 1000);
	ret += (tv.tv_usec / 1000);
	*dest = ret;
	return (SUCCESS);
}
