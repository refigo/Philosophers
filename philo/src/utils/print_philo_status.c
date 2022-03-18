/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_philo_status.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 13:22:09 by mgo               #+#    #+#             */
/*   Updated: 2022/03/18 15:20:55 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_philo_died(t_philo *philo, struct timeval time_now)
{
	struct timeval	time_start;
	long long		timestamp_ms;

	time_start = philo->data->time_start_dining;
	timestamp_ms = get_ms_timeval(time_now) - get_ms_timeval(time_start);
	printf("%lld\t%d died.\n", timestamp_ms, philo->number);
}

// to use t_status?
void	print_philo_status(t_philo *philo, char *status)
{
	struct timeval	time_now;
	struct timeval	time_start;
	long long		timestamp_ms;

	pthread_mutex_lock(&philo->data->mutex_flag_finish);
	if (philo->data->flag_finish != TRUE)
	{
		gettimeofday(&time_now, NULL);
		time_start = philo->data->time_start_dining;
		timestamp_ms = get_ms_timeval(time_now) - get_ms_timeval(time_start);
		printf("%lld\t%d %s.\n", timestamp_ms, philo->number, status);
	}
	pthread_mutex_unlock(&philo->data->mutex_flag_finish);
}
