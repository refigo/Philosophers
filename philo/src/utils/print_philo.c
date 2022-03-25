/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 16:21:06 by mgo               #+#    #+#             */
/*   Updated: 2022/03/25 16:21:10 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

void	print_philo_died(t_philo *philo, long int ms_now)
{
	long int	timestamp_ms;

	timestamp_ms = ms_now - philo->data->ms_start_dining;
	printf("%ld\t%d died\n", timestamp_ms, philo->number);
}

void	print_philo_status(t_philo *philo, char *status)
{
	long int	timestamp_ms;

	pthread_mutex_lock(&philo->data->mutex_flag_finish);
	if (philo->data->flag_finish == FALSE)
	{
		set_time_ms(&timestamp_ms);
		timestamp_ms -= philo->data->ms_start_dining;
		printf("%ld\t%d %s\n", timestamp_ms, philo->number, status);
	}
	pthread_mutex_unlock(&philo->data->mutex_flag_finish);
}
