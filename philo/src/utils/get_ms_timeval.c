/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ms_timeval.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 13:21:39 by mgo               #+#    #+#             */
/*   Updated: 2022/03/19 15:02:57 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>

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
