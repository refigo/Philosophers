/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 10:21:50 by mgo               #+#    #+#             */
/*   Updated: 2022/03/21 16:52:46 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	check_having_eaten_up_to_finish(t_setting *data)
{
	if (data->num_philos_done == data->num_of_philos)
	{
		printf("Finish: All philosophers have eaten up each dishes!\n");
		data->flag_finish = TRUE;
	}
}

void	*monitor_having_eaten_up_routine(void *arg)
{
	t_setting	*data;

	data = arg;
	while (data->flag_finish == FALSE)
	{
		pthread_mutex_lock(&data->mutex_flag_finish);
		if (data->flag_finish == FALSE)
			check_having_eaten_up_to_finish(data);
		pthread_mutex_unlock(&data->mutex_flag_finish);
	}
	return (NULL);
}

static void	check_death_to_finish(t_philo *philo)
{
	long int	ms_now;
	long int	diff_time_eat_now_last;

	ms_now = get_time_ms();
	diff_time_eat_now_last = ms_now - philo->ms_eat_last;
	if (diff_time_eat_now_last >= philo->data->time_to_die)
	{
		print_philo_died(philo, ms_now);
		philo->data->flag_finish = TRUE;
	}
}

void	*monitor_death_routine(void *arg)
{
	t_philo		*philo;

	philo = arg;
	while (philo->data->flag_finish == FALSE)
	{
		pthread_mutex_lock(&philo->mutex_check_starvation);
		pthread_mutex_lock(&philo->data->mutex_flag_finish);
		if (philo->data->flag_finish == FALSE)
			check_death_to_finish(philo);
		pthread_mutex_unlock(&philo->data->mutex_flag_finish);
		pthread_mutex_unlock(&philo->mutex_check_starvation);
	}
	return (NULL);
}
