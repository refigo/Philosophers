/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   have_dining_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 20:26:53 by mgo               #+#    #+#             */
/*   Updated: 2022/04/06 20:26:54 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <unistd.h> // fork()
#include <stdlib.h> // exit()

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
			sem_post(data->termination_sem);
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
			sem_post(philo->data->termination_sem);
			break ;
		}
		sem_post(philo->data->print_mutex_sem);
	}
	return (NULL);
}

void	process_philo(t_philo *philo)
{
	pthread_create(&(philo->monitor_death_thread), NULL, monitor_death_routine, philo);
	//if (philo->number % 2 == 0)
	while (TRUE)
	{
		//taking_forks(philo);
		//eating
		//sleeping
		//thinking
	}
}

int	invite_philos(t_setting *data)
{
	int	i;

	pthread_create(&(data->monitor_full_thread), NULL, monitor_full_routine, data);
	set_time_ms(&(data->ms_start_dining));
	i = -1;
	while (++i < data->num_of_philos)
	{
		data->philos[i].ms_eat_last = data->ms_start_dining;
		data->philos[i].philo_pid = fork();
		if (data->philos[i].philo_pid == 0)
		{
			process_philo(&(data->philos[i]));
			exit(TRUE);
		}
		else if (data->philos[i].philo_pid == -1)
			return (FAIL);
	}
	sem_wait(data->termination_sem); // todo: error check
	return (SUCCESS);
}

int	have_dining(t_setting *data)
{
	if (data->num_of_philos == 0)
	{
		printf("Finish: No one is invited!\n");
		return (SUCCESS);
	}
	invite_philos(data);
	//close_when_finished
	return (SUCCESS);
}
