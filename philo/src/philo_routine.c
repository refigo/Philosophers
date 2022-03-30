/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 13:19:24 by mgo               #+#    #+#             */
/*   Updated: 2022/03/30 13:11:35 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

int	sleep_shortly_ms(long int ms_sleep)
{
	long int	ms_dest;
	long int	ms_now;

	set_time_ms(&ms_dest);
	set_time_ms(&ms_now);
	ms_dest += ms_sleep;
	while (ms_dest > ms_now)
	{
		if (usleep(EPSILON))
			return (FALSE);
		set_time_ms(&ms_now);
	}
	return (TRUE);
}

static void	taking_forks(t_philo *philo)
{
	t_setting	*data;

	data = philo->data;
	pthread_mutex_lock(philo->l_fork);
	if (print_philo_status(philo, "has taken a fork") == FAIL)
		pthread_mutex_unlock(&(philo->data->mutex_error_handling));
	while (data->num_of_philos == 1 && data->flag_finish == FALSE)
		;
	if (data->num_of_philos == 1 && data->flag_finish == TRUE)
		return ;
	pthread_mutex_lock(philo->r_fork);
	if (print_philo_status(philo, "has taken a fork") == FAIL)
		pthread_mutex_unlock(&(philo->data->mutex_error_handling));
}

static void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex_check_starvation);
	if (print_philo_status(philo, "is eating") == FAIL)
		pthread_mutex_unlock(&(philo->data->mutex_error_handling));
	set_time_ms(&(philo->ms_eat_last));
	(philo->num_eat)++;
	if (philo->num_eat == philo->data->num_of_times_each_must_eat)
		(philo->data->num_philos_done)++;
	pthread_mutex_unlock(&philo->mutex_check_starvation);

	if (sleep_shortly_ms(philo->data->time_to_eat) == FALSE)
		pthread_mutex_unlock(&(philo->data->mutex_error_handling));
	/*
	if (usleep(philo->data->time_to_eat * 1000) == -1)
		pthread_mutex_unlock(&(philo->data->mutex_error_handling));
	*/

	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

static void	sleeping(t_philo *philo)
{
	if (print_philo_status(philo, "is sleeping") == FAIL)
		pthread_mutex_unlock(&(philo->data->mutex_error_handling));

	if (sleep_shortly_ms(philo->data->time_to_sleep) == FALSE)
		pthread_mutex_unlock(&(philo->data->mutex_error_handling));
	/*
	if (usleep(philo->data->time_to_sleep * 1000) == -1)
		pthread_mutex_unlock(&(philo->data->mutex_error_handling));
	*/
}

static void	thinking(t_philo *philo)
{
	if (print_philo_status(philo, "is thinking") == FAIL)
		pthread_mutex_unlock(&(philo->data->mutex_error_handling));
	if (usleep(200) == -1)
		pthread_mutex_unlock(&(philo->data->mutex_error_handling));
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if ((philo->number) % 2 == 0)
	{
		if (usleep(philo->data->time_to_eat * 500) == -1)
			pthread_mutex_unlock(&(philo->data->mutex_error_handling));
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
