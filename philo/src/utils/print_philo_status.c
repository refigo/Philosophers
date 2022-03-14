/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_philo_status.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 13:22:09 by mgo               #+#    #+#             */
/*   Updated: 2022/03/14 13:22:59 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_philo_status(t_philo *philo, char *status)
{
	struct timeval	time_now;
	struct timeval	time_start;
	long long		timestamp_ms;

	gettimeofday(&time_now, NULL);
	time_start = philo->data->time_start_dining;
	timestamp_ms = get_ms_timeval(time_now) - get_ms_timeval(time_start);
	printf("%lld\t%d %s\n", timestamp_ms, philo->number, status);
}
