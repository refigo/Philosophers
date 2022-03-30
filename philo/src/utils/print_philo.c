/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 16:21:06 by mgo               #+#    #+#             */
/*   Updated: 2022/03/30 13:39:57 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

int	print_philo_died(t_philo *philo, long int ms_now)
{
	long int	timestamp_ms;

	timestamp_ms = ms_now - philo->data->ms_start_dining;
	if (printf("%ld %d died\n", timestamp_ms, philo->number) < 0)
		return (FAIL);
	return (SUCCESS);
}

int	print_philo_status(t_philo *philo, char *status)
{
	long int	timestamp_ms;
	int			ret;

	ret = SUCCESS;
	pthread_mutex_lock(&philo->data->mutex_flag_finish);
	if (philo->data->flag_finish == FALSE)
	{
		set_time_ms(&timestamp_ms);
		timestamp_ms -= philo->data->ms_start_dining;
		if (printf("%ld %d %s\n", timestamp_ms, philo->number, status) < 0)
			ret = FAIL;
	}
	pthread_mutex_unlock(&philo->data->mutex_flag_finish);
	return (ret);
}
