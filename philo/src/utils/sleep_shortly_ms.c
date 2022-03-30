/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep_shortly_ms.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 16:01:45 by mgo               #+#    #+#             */
/*   Updated: 2022/03/30 16:20:31 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
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
