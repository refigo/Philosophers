/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 13:19:24 by mgo               #+#    #+#             */
/*   Updated: 2022/03/18 11:38:30 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

static void	taking_forks(t_philo *philo)
{
	t_setting	*data;

	data = philo->data;
	pthread_mutex_lock(philo->l_fork);
	pthread_mutex_lock(&philo->data->mutex_flag_finish);
	print_philo_status(philo, "has taken a fork");
	pthread_mutex_unlock(&philo->data->mutex_flag_finish);
	// exception for one philosopher
	while (data->num_of_philos == 1 && data->flag_finish == FALSE)
		;
	if (data->flag_finish == TRUE)
		return ;
	pthread_mutex_lock(philo->r_fork);
	pthread_mutex_lock(&philo->data->mutex_flag_finish);
	print_philo_status(philo, "has taken a fork");
	pthread_mutex_unlock(&philo->data->mutex_flag_finish);
}

static void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex_check_starvation);
	gettimeofday(&philo->time_eat_last, NULL);
	pthread_mutex_lock(&philo->data->mutex_flag_finish);
	print_philo_status(philo, "is eating");
	pthread_mutex_unlock(&philo->data->mutex_flag_finish);
	pthread_mutex_lock(&philo->data->mutex_flag_finish);
	(philo->num_eat)++;
	if (philo->num_eat == philo->data->num_of_times_each_must_eat)
		(philo->data->num_philos_done)++;
	pthread_mutex_unlock(&philo->data->mutex_flag_finish);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(&philo->mutex_check_starvation);
}

static void	sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_flag_finish);
	print_philo_status(philo, "is sleeping");
	pthread_mutex_unlock(&philo->data->mutex_flag_finish);
	usleep(philo->data->time_to_sleep * 1000);
}

static void	thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_flag_finish);
	print_philo_status(philo, "is thinking");
	pthread_mutex_unlock(&philo->data->mutex_flag_finish);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if ((philo->number) % 2 == 0)
		usleep(philo->data->time_to_eat * 1000);
	while (philo->data->flag_finish == FALSE)
	{
		taking_forks(philo);
		if (philo->data->flag_finish == TRUE)
			break ;
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
