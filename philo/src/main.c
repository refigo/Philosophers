/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 09:41:00 by mgo               #+#    #+#             */
/*   Updated: 2022/03/08 15:56:23 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
// check status

void	print_philo_status(t_philo *philo, char *status)
{
	struct timeval	time_now;
	long long		timestamp_in_ms;

	gettimeofday(&time_now, NULL);
	timestamp_in_ms = time_now.tv_sec - philo->data->time_start_dining.tv_sec;
	timestamp_in_ms += time_now.tv_usec / 1000 - philo->data->time_start_dining.tv_usec / 1000;
	printf("%lld %d %s\n", timestamp_in_ms, philo->number, status);
}

void	taking_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	print_philo_status(philo, "has taken a fork");
	pthread_mutex_lock(philo->r_fork);
	print_philo_status(philo, "has taken a fork");
}

#include <unistd.h>
void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	printf("philo[%d]: hi\n", philo->number);
	if ((philo->number) % 2 == 0)
		usleep(100 * 1000);
	taking_forks(philo);

	// eat
	// sleep
	// think
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	return (NULL);
}

void	have_dining(t_setting *data)
{
	int	i;

	gettimeofday(&(data->time_start_dining), NULL);
	i = -1;
	while (++i < data->num_of_philos)
	{
		pthread_create(&(data->philos[i].thread), NULL, \
				philo_routine, &(data->philos[i]));
		//check_death_for_finish
	}
	i = -1;
	while (++i < data->num_of_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
	}
}

int	main(int argc, char **argv)
{
	t_setting	data;

	if ((argc != 5) && (argc != 6))
		return (error_with_msg("the number of args wrong!"));
	if (set_data(&data, argc, argv) == FAIL)
		return (FAIL);
	have_dining(&data);

	//clear_data();

	//test_overall(&data);
	return (SUCCESS);
}
//error exception with free all???
