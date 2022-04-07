/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 21:39:07 by mgo               #+#    #+#             */
/*   Updated: 2022/04/06 21:39:07 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*monitor_error_routine(void *arg)
{
	t_setting	*data;

	data = (t_setting *)arg;
	sem_wait(data->error_sem);
	sem_post(data->print_mutex_sem);
	data->is_error_in_philo = TRUE;
	error_with_msg("Error handling activated in a philo process.");
	sem_post(data->finish_sem);
	return (NULL);
}

void	*monitor_full_routine(void *arg)
{
	t_setting	*data;
	int			count_full;

	data = (t_setting *)arg;
	count_full = 0;
	while (TRUE)
	{
		sem_wait(data->full_sem); // todo: error
		count_full++;
		if (count_full == data->num_of_philos)
		{
			sem_wait(data->print_mutex_sem);
			printf("Finish: full\n");
			sem_post(data->finish_sem);
			break ;
		}
	}
	return (NULL);
}

void	*monitor_death_routine(void *arg)
{
	t_philo		*philo;
	long int	ms_now;
	long int	diff_time_eating;

	philo = (t_philo *)arg;
	sleep_shortly_ms(philo->data->time_to_die - 10);
	while (TRUE)
	{
		sem_wait(philo->data->print_mutex_sem);
		set_time_ms(&ms_now);
		diff_time_eating = ms_now - philo->ms_eat_last;
		if (diff_time_eating >= philo->data->time_to_die)
		{
			print_philo_died(philo, ms_now);
			sem_post(philo->data->finish_sem);
			break ;
		}
		sem_post(philo->data->print_mutex_sem);
	}
	return (NULL);
}
