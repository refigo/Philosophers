/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 09:41:00 by mgo               #+#    #+#             */
/*   Updated: 2022/03/10 15:16:14 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
// check status

long long	get_ms_timeval(struct timeval tv)
{
	long long	ret;

	ret = (tv.tv_sec * 1000);
	ret += (tv.tv_usec / 1000);
	return (ret);
}

void	print_philo_status(t_philo *philo, char *status)
{
	struct timeval	time_now;
	struct timeval	time_start;
	long long		timestamp_ms;

	gettimeofday(&time_now, NULL);
	time_start = philo->data->time_start_dining;
	timestamp_ms = get_ms_timeval(time_now) - get_ms_timeval(time_start);
	printf("%lld\t%d %s\n", timestamp_ms, philo->number, status);
}

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
	struct timeval	time_eat_now;
	long long		diff_time_eat_now_last;

	gettimeofday(&time_eat_now, NULL);
	diff_time_eat_now_last = \
		get_ms_timeval(time_eat_now) - get_ms_timeval(philo->time_eat_last);
	printf("diff_time_eat_now_last: [%lld]\n", diff_time_eat_now_last);
	if (diff_time_eat_now_last > philo->data->time_to_die)
	{
		print_philo_status(philo, "died");
		//todo: use mutex_for_check
	}
	else
	{
		print_philo_status(philo, "is eating");
		usleep(philo->data->time_to_eat * 1000);
	}
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
	//printf("philo[%d]: hi\n", philo->number);
	if ((philo->number) % 2 == 0)
		usleep(philo->data->time_to_eat * 1000);
	taking_forks(philo);
	eating(philo);
	sleeping(philo);
	thinking(philo);
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
