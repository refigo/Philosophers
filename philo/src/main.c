/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 09:41:00 by mgo               #+#    #+#             */
/*   Updated: 2022/03/18 10:23:32 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	have_dining(t_setting *data)
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

static void	clear_data(t_setting *data)
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
	have_dining(&data);
	//test_overall(&data);
	clear_data(&data);
	//system("leaks philo");
	return (SUCCESS);
}
//error exception with free all???
