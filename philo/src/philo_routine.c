/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 13:19:24 by mgo               #+#    #+#             */
/*   Updated: 2022/03/30 19:25:29 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

static void	taking_forks(t_philo *philo)
{
	t_setting	*data;

	data = philo->data;
	if (pthread_mutex_lock(philo->l_fork) != SUCCESS \
		|| print_philo_status(philo, "has taken a fork") == FAIL)
		pthread_mutex_unlock(&(philo->data->mutex_error_handling));
	if (data->num_of_philos == 1)
	{
		while (data->flag_finish == FALSE)
			;
		return ;
	}
	if (pthread_mutex_lock(philo->r_fork) != SUCCESS \
		|| print_philo_status(philo, "has taken a fork") == FAIL)
		pthread_mutex_unlock(&(philo->data->mutex_error_handling));
}

static void	eating(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->mutex_check_starvation) != SUCCESS \
		|| print_philo_status(philo, "is eating") == FAIL \
		|| set_time_ms(&(philo->ms_eat_last)) == FAIL \
		|| pthread_mutex_unlock(&philo->mutex_check_starvation))
		pthread_mutex_unlock(&(philo->data->mutex_error_handling));
	if (philo->num_eat < philo->data->num_of_times_each_must_eat)
	{
		(philo->num_eat)++;
		if (philo->num_eat == philo->data->num_of_times_each_must_eat)
			(philo->data->num_philos_full) += 1;
	}
	if (sleep_shortly_ms(philo->data->time_to_eat) == FAIL \
		|| pthread_mutex_unlock(philo->l_fork) != SUCCESS\
		|| pthread_mutex_unlock(philo->r_fork) != SUCCESS)
		pthread_mutex_unlock(&(philo->data->mutex_error_handling));
}

static void	sleeping(t_philo *philo)
{
	if (print_philo_status(philo, "is sleeping") == FAIL \
		|| sleep_shortly_ms(philo->data->time_to_sleep) == FAIL)
		pthread_mutex_unlock(&(philo->data->mutex_error_handling));
}

static void	thinking(t_philo *philo)
{
	if (print_philo_status(philo, "is thinking") == FAIL \
		|| usleep(300) == FAIL)
		pthread_mutex_unlock(&(philo->data->mutex_error_handling));
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if ((philo->number) % 2 == 0)
		if (sleep_shortly_ms(philo->data->time_to_eat * 0.5) == FAIL)
			pthread_mutex_unlock(&(philo->data->mutex_error_handling));
	while (philo->data->flag_finish == FALSE)
	{
		taking_forks(philo);
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
