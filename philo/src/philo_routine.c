/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 13:19:24 by mgo               #+#    #+#             */
/*   Updated: 2022/03/15 13:22:25 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

static void	taking_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_flag_finish);
	if (philo->data->flag_finish == FALSE)
	{
		pthread_mutex_lock(philo->l_fork);
		print_philo_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->r_fork);
		print_philo_status(philo, "has taken a fork");
	}
	pthread_mutex_unlock(&philo->data->mutex_flag_finish);
}

static void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex_check_starvation);
	gettimeofday(&philo->time_eat_last, NULL);
	pthread_mutex_lock(&philo->data->mutex_flag_finish);
	if (philo->data->flag_finish == FALSE)
		print_philo_status(philo, "is eating");
	pthread_mutex_unlock(&philo->data->mutex_flag_finish);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(&philo->mutex_check_starvation);
}

static void	sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_flag_finish);
	if (philo->data->flag_finish == FALSE)
		print_philo_status(philo, "is sleeping");
	pthread_mutex_unlock(&philo->data->mutex_flag_finish);
	usleep(philo->data->time_to_sleep * 1000);
}

static void	thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_flag_finish);
	if (philo->data->flag_finish == FALSE)
		print_philo_status(philo, "is thinking");
	pthread_mutex_unlock(&philo->data->mutex_flag_finish);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if ((philo->number) % 2 == 0)
		usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_lock(&philo->data->mutex_flag_finish);
	while (philo->data->flag_finish == FALSE)
	{
		pthread_mutex_unlock(&philo->data->mutex_flag_finish);
		taking_forks(philo);
		eating(philo);
		sleeping(philo);
		thinking(philo);
		pthread_mutex_lock(&philo->data->mutex_flag_finish);
	}
	pthread_mutex_unlock(&philo->data->mutex_flag_finish);
	return (NULL);
}
