/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 10:21:50 by mgo               #+#    #+#             */
/*   Updated: 2022/03/18 10:22:27 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_routine(void *arg)
{
	t_philo			*philo;
	struct timeval	time_now;
	long long		diff_time_eat_now_last;

	philo = arg;
	while (philo->data->flag_finish == FALSE)
	{
		pthread_mutex_lock(&philo->mutex_check_starvation);
		pthread_mutex_lock(&philo->data->mutex_flag_finish);
		gettimeofday(&time_now, NULL);
		diff_time_eat_now_last = \
			get_ms_timeval(time_now) - get_ms_timeval(philo->time_eat_last);
		if (diff_time_eat_now_last > philo->data->time_to_die && philo->data->flag_finish == FALSE)
		{
			print_philo_status(philo, "died");
			philo->data->flag_finish = TRUE;
		}
		if (philo->data->num_philos_done == philo->data->num_of_philos && philo->data->flag_finish == FALSE)
		{
			printf("Finishes!\n");
			philo->data->flag_finish = TRUE;
		}
		pthread_mutex_unlock(&philo->data->mutex_flag_finish);
		pthread_mutex_unlock(&philo->mutex_check_starvation);
	}
	return (NULL);
}
