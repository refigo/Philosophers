/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 09:41:00 by mgo               #+#    #+#             */
/*   Updated: 2022/03/14 12:59:34 by mgo              ###   ########.fr       */
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
	pthread_mutex_lock(&philo->mutex_check_starvation);
	philo->time_eat_last = philo->data->time_start_dining;
	pthread_mutex_unlock(&philo->mutex_check_starvation);
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

void	*monitor_routine(void *arg)
{
	t_philo			*philo;
	struct timeval	time_now;
	long long		diff_time_eat_now_last;

	philo = arg;
	while (philo->data->flag_finish == FALSE)
	{
		pthread_mutex_lock(&philo->data->mutex_flag_finish);
		pthread_mutex_lock(&philo->mutex_check_starvation);
		gettimeofday(&time_now, NULL);
		diff_time_eat_now_last = \
			get_ms_timeval(time_now) - get_ms_timeval(philo->time_eat_last);
		//printf("diff_time_eat_now_last: [%lld]\n", diff_time_eat_now_last);
		if (diff_time_eat_now_last > philo->data->time_to_die)
		{
			print_philo_status(philo, "died");
			philo->data->flag_finish = TRUE;
		}
		pthread_mutex_unlock(&philo->mutex_check_starvation);
		pthread_mutex_unlock(&philo->data->mutex_flag_finish);
	}
	return (NULL);
}

void	have_dining(t_setting *data)
{
	pthread_t	monitor_thread;
	int	i;

	gettimeofday(&(data->time_start_dining), NULL);
	i = -1;
	while (++i < data->num_of_philos)
	{
		pthread_create(&(data->philos[i].thread), NULL, \
				philo_routine, &(data->philos[i]));
		//check_death_for_finish
		pthread_create(&monitor_thread, NULL, \
				monitor_routine, &(data->philos[i]));
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
