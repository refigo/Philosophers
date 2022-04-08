/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_time_ms_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 20:37:50 by mgo               #+#    #+#             */
/*   Updated: 2022/04/06 20:37:51 by mgo              ###   ########.fr       */
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
