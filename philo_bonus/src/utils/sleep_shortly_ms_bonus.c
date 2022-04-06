/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep_shortly_ms_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 21:11:11 by mgo               #+#    #+#             */
/*   Updated: 2022/04/06 21:11:19 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <unistd.h>

int	sleep_shortly_ms(long int ms_sleep)
{
	long int	ms_dest;
	long int	ms_now;

	set_time_ms(&ms_dest);
	ms_dest += ms_sleep;
	set_time_ms(&ms_now);
	while (ms_dest > ms_now)
	{
		if (usleep(EPSILON) == FAIL)
			return (FAIL);
		set_time_ms(&ms_now);
	}
	return (SUCCESS);
}
