/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 13:19:24 by mgo               #+#    #+#             */
/*   Updated: 2022/03/24 14:31:39 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

static void	taking_forks(t_philo *philo)
{
	t_setting	*data;

	data = philo->data;
	pthread_mutex_lock(philo->l_fork);
	print_philo_status(philo, "has taken a fork");
	while (data->num_of_philos == 1 && data->flag_finish == FALSE)
		;
	if (data->num_of_philos == 1 && data->flag_finish == TRUE)
		return ;
	pthread_mutex_lock(philo->r_fork);
	print_philo_status(philo, "has taken a fork");
}

static void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex_check_starvation);
	print_philo_status(philo, "is eating");
	set_time_ms(&(philo->ms_eat_last));
	(philo->num_eat)++;
	if (philo->num_eat == philo->data->num_of_times_each_must_eat)
		(philo->data->num_philos_done)++;

	usleep(philo->data->time_to_eat * 1000);
	/*
	if (usleep(philo->data->time_to_eat * 1000) == -1)
		pthread_mutex_unlock(&(philo->data->mutex_error_management));
	*/

	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(&philo->mutex_check_starvation);
}

static void	sleeping(t_philo *philo)
{
	print_philo_status(philo, "is sleeping");

	usleep(philo->data->time_to_sleep * 1000);
	/*
	if (usleep(philo->data->time_to_sleep * 1000) == -1)
		pthread_mutex_unlock(&(philo->data->mutex_error_management));
	*/
}

static void	thinking(t_philo *philo)
{
	print_philo_status(philo, "is thinking");

	usleep(200);
	/*
	if (usleep(200) == -1)
		pthread_mutex_unlock(&(philo->data->mutex_error_management));
	*/
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if ((philo->number) % 2 == 0)
	{
		usleep(philo->data->time_to_eat * 500);
		/*
		if (usleep(philo->data->time_to_eat * 500) == -1)
			pthread_mutex_unlock(&(philo->data->mutex_error_management));
		*/
	}
	while (philo->data->flag_finish == FALSE)
	{
		taking_forks(philo);
		if (philo->data->num_of_philos == 1 && philo->data->flag_finish == TRUE)
			break ;
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
