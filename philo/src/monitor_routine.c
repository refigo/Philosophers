/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 10:21:50 by mgo               #+#    #+#             */
/*   Updated: 2022/03/21 16:38:56 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_routine(void *arg)
{

}

static void	check_condition_to_finish(t_philo *philo)
{
	long long		ms_now;
	long long		diff_time_eat_now_last;

	ms_now = get_time_ms();
	diff_time_eat_now_last = ms_now - philo->ms_eat_last;
	if (diff_time_eat_now_last >= philo->data->time_to_die)
	{
		print_philo_died(philo, ms_now);
		philo->data->flag_finish = TRUE;
	}
	else if (philo->data->num_philos_done == philo->data->num_of_philos)
	{
		printf("Finish: All philosophers have eaten up each dishes!\n");
		philo->data->flag_finish = TRUE;
	}
}

void	*monitor_routine(void *arg)
{
	t_philo			*philo;

	philo = arg;
	while (philo->data->flag_finish == FALSE)
	{
		pthread_mutex_lock(&philo->mutex_check_starvation);
		pthread_mutex_lock(&philo->data->mutex_flag_finish);
		if (philo->data->flag_finish == FALSE)
			check_condition_to_finish(philo);
		pthread_mutex_unlock(&philo->data->mutex_flag_finish);
		pthread_mutex_unlock(&philo->mutex_check_starvation);
	}
	return (NULL);
}
