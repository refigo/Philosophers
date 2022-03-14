/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 13:19:24 by mgo               #+#    #+#             */
/*   Updated: 2022/03/14 13:29:57 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

static void	taking_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	print_philo_status(philo, "has taken a fork");
	pthread_mutex_lock(philo->r_fork);
	print_philo_status(philo, "has taken a fork");
}

static void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex_check_starvation);
	gettimeofday(&philo->time_eat_last, NULL);
	if (philo->data->flag_finish == TRUE)
	{
		return ;
	}
	else
	{
		print_philo_status(philo, "is eating");
		usleep(philo->data->time_to_eat * 1000);
	}
	pthread_mutex_unlock(&philo->mutex_check_starvation);
}

static void	sleeping(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	print_philo_status(philo, "is sleeping");
	usleep(philo->data->time_to_sleep * 1000);
}

static void	thinking(t_philo *philo)
{
	print_philo_status(philo, "is thinking");
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	philo->time_eat_last = philo->data->time_start_dining;
	if ((philo->number) % 2 == 0)
		usleep(philo->data->time_to_eat * 1000);
	while (philo->data->flag_finish == FALSE)
	{
		taking_forks(philo);
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}