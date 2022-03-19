/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_philo_status.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 13:22:09 by mgo               #+#    #+#             */
/*   Updated: 2022/03/19 13:46:38 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_philo_died(t_philo *philo, long long ms_now)
{
	long long		timestamp_ms;

	timestamp_ms = ms_now - philo->data->ms_start_dining;
	printf("%lld\t%d died\n", timestamp_ms, philo->number);
}

// to use e_status?
void	print_philo_status(t_philo *philo, char *status)
{
	long long		timestamp_ms;

	pthread_mutex_lock(&philo->data->mutex_flag_finish);
	if (philo->data->flag_finish == FALSE)
	{
		timestamp_ms = get_time_ms() - philo->data->ms_start_dining;
		printf("%lld\t%d %s\n", timestamp_ms, philo->number, status);
	}
	pthread_mutex_unlock(&philo->data->mutex_flag_finish);
}
