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
	if (sem_wait(data->forks) == FAIL \
	|| print_philo_status(philo, "has taken a fork") == FAIL \
	|| sem_wait(data->forks) == FAIL \
	|| print_philo_status(philo, "has taken a fork") == FAIL)
		sem_post(data->error_sem);
}

void	eating(t_philo *philo)
{
	if (print_philo_status(philo, "is eating") == FAIL \
	|| set_time_ms(&(philo->ms_eat_last)) == FAIL)
		sem_post(philo->data->error_sem);
	if (philo->num_eat < philo->data->num_of_times_each_must_eat)
	{
		(philo->num_eat)++;
		if (philo->num_eat == philo->data->num_of_times_each_must_eat)
			sem_post(philo->data->full_sem);
	}
	if (sleep_shortly_ms(philo->data->time_to_eat) == FAIL \
	|| sem_post(philo->data->forks) == FAIL \
	|| sem_post(philo->data->forks) == FAIL)
		sem_post(philo->data->error_sem);
}

void	sleeping(t_philo *philo)
{
	if (print_philo_status(philo, "is sleeping") == FAIL \
	|| sleep_shortly_ms(philo->data->time_to_sleep) == FAIL)
		sem_post(philo->data->error_sem);
}

void	thinking(t_philo *philo)
{
	if (print_philo_status(philo, "is thinking") == FAIL)
		sem_post(philo->data->error_sem);
}

void	process_philo(t_philo *philo)
{
	if (pthread_create(&(philo->monitor_death_thread), NULL, \
			monitor_death_routine, philo) != SUCCESS)
		sem_post(philo->data->error_sem);
	if (pthread_detach(philo->monitor_death_thread) != SUCCESS)
		sem_post(philo->data->error_sem);
	while (TRUE)
	{
		taking_forks(philo);
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
}
