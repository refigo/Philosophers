/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_philo_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 21:54:59 by mgo               #+#    #+#             */
/*   Updated: 2022/04/06 21:55:03 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <unistd.h>

void	taking_forks(t_philo *philo)
{
	t_setting	*data;

	data = philo->data;
	sem_wait(data->forks);
	print_philo_status(philo, "has taken a fork");
	sem_wait(data->forks);
	print_philo_status(philo, "has taken a fork");
}

void	eating(t_philo *philo)
{
	print_philo_status(philo, "is eating");
	set_time_ms(&(philo->ms_eat_last));
	if (philo->num_eat < philo->data->num_of_times_each_must_eat)
	{
		(philo->num_eat)++;
		if (philo->num_eat == philo->data->num_of_times_each_must_eat)
			sem_post(philo->data->full_sem);
	}
	sleep_shortly_ms(philo->data->time_to_eat);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

void	sleeping(t_philo *philo)
{
	print_philo_status(philo, "is sleeping");
	sleep_shortly_ms(philo->data->time_to_sleep);
}

void	thinking(t_philo *philo)
{
	print_philo_status(philo, "is sleeping");
	usleep(300); // todo: consider
}

void	process_philo(t_philo *philo)
{
	pthread_create(&(philo->monitor_death_thread), NULL, \
	monitor_death_routine, philo);
	pthread_detach(philo->monitor_death_thread);
	if (philo->number % 2 == 0)
		usleep(300);
	while (TRUE)
	{
		taking_forks(philo);
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
}
