/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 09:41:00 by mgo               #+#    #+#             */
/*   Updated: 2022/03/17 20:33:11 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
// check status

void	*monitor_routine(void *arg)
{
	t_philo			*philo;
	struct timeval	time_now;
	long long		diff_time_eat_now_last;

	philo = arg;
	while (philo->data->flag_finish == FALSE)
	{
		pthread_mutex_lock(&philo->mutex_check_starvation);
		pthread_mutex_lock(&philo->data->mutex_flag_finish);
		gettimeofday(&time_now, NULL);
		diff_time_eat_now_last = \
			get_ms_timeval(time_now) - get_ms_timeval(philo->time_eat_last);
		if (diff_time_eat_now_last > philo->data->time_to_die && philo->data->flag_finish == FALSE)
		{
			print_philo_status(philo, "died");
			philo->data->flag_finish = TRUE;
		}
		if (philo->data->num_philos_done == philo->data->num_of_philos && philo->data->flag_finish == FALSE)
		{
			printf("Finishes!\n");
			philo->data->flag_finish = TRUE;
		}
		pthread_mutex_unlock(&philo->data->mutex_flag_finish);
		pthread_mutex_unlock(&philo->mutex_check_starvation);
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
		data->philos[i].time_eat_last = data->time_start_dining;
		pthread_create(&(data->philos[i].thread), NULL, \
				philo_routine, &(data->philos[i]));
		pthread_create(&monitor_thread, NULL, \
				monitor_routine, &(data->philos[i]));
		pthread_detach(monitor_thread);
	}
	i = -1;
	while (++i < data->num_of_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
	}
}

void	clear_data(t_setting *data)
{
	int	i;

	i = -1;
	while (++i < data->num_of_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
	}
	free(data->philos);
	free(data->forks);
}

int	main(int argc, char **argv)
{
	t_setting	data;

	if ((argc != 5) && (argc != 6))
		return (error_with_msg("the number of args wrong!"));
	if (set_data(&data, argc, argv) == FAIL)
		return (FAIL);
	//test_overall(&data);
	have_dining(&data);
	clear_data(&data);
	return (SUCCESS);
}
//error exception with free all???
