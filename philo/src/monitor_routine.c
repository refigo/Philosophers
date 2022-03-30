/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 10:21:50 by mgo               #+#    #+#             */
/*   Updated: 2022/03/30 19:23:09 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

static void	check_full_to_finish(t_setting *data)
{
	if (data->num_philos_full == data->num_of_philos)
	{
		printf("Finish: All philosophers are full!\n");
		data->flag_finish = TRUE;
	}
}

void	*monitor_full_routine(void *arg)
{
	t_setting	*data;

	data = arg;
	while (data->flag_finish == FALSE)
	{
		pthread_mutex_lock(&(data->mutex_flag_finish));
		if (data->flag_finish == FALSE)
			check_full_to_finish(data);
		pthread_mutex_unlock(&(data->mutex_flag_finish));
	}
	return (NULL);
}

static void	check_death_to_finish(t_philo *philo)
{
	long int	ms_now;
	long int	diff_time_eating;

	set_time_ms(&ms_now);
	diff_time_eating = ms_now - philo->ms_eat_last;
	if (diff_time_eating >= philo->data->time_to_die)
	{
		print_philo_died(philo, ms_now);
		philo->data->flag_finish = TRUE;
	}
}

void	*monitor_death_routine(void *arg)
{
	t_setting	*data;
	int			i;

	data = arg;
	while (data->flag_finish == FALSE)
	{
		i = -1;
		while (++i < data->num_of_philos && data->flag_finish == FALSE)
		{
			pthread_mutex_lock(&(data->philos[i].mutex_check_starvation));
			pthread_mutex_lock(&(data->mutex_flag_finish));
			if (data->flag_finish == FALSE)
				check_death_to_finish(&(data->philos[i]));
			pthread_mutex_unlock(&(data->mutex_flag_finish));
			pthread_mutex_unlock(&(data->philos[i].mutex_check_starvation));
		}
	}
	return (NULL);
}
