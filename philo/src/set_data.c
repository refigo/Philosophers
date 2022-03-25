/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:43:13 by mgo               #+#    #+#             */
/*   Updated: 2022/03/25 16:06:44 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>

static int	set_and_check_args(t_setting *data, int argc, char **argv)
{
	data->num_of_philos = mgo_atoi(argv[1]);
	data->time_to_die = mgo_atoi(argv[2]);
	data->time_to_eat = mgo_atoi(argv[3]);
	data->time_to_sleep = mgo_atoi(argv[4]);
	if (argc == 6)
		data->num_of_times_each_must_eat = mgo_atoi(argv[5]);
	if (data->num_of_philos < 0)
		return (error_with_msg("number_of_philosophers"));
	if (data->time_to_die < 0)
		return (error_with_msg("time_to_die"));
	if (data->time_to_eat < 0)
		return (error_with_msg("time_to_eat"));
	if (data->time_to_sleep < 0)
		return (error_with_msg("time_to_sleep"));
	if ((argc == 6) && (data->num_of_times_each_must_eat <= 0))
		return (error_with_msg("number_of_times_each_philosopher_must_eat"));
	return (SUCCESS);
}

static int	set_forks_and_philos(t_setting *data)
{
	int	i;

	data->forks = mgo_calloc(data->num_of_philos, sizeof(pthread_mutex_t));
	data->philos = mgo_calloc(data->num_of_philos, sizeof(t_philo));
	if ((data->philos == NULL) || (data->forks == NULL))
		return (error_with_msg("malloc failed"));
	i = -1;
	while (++i < data->num_of_philos)
	{
		if (pthread_mutex_init(&(data->forks[i]), NULL) == FAIL)
			return (error_with_msg("mutex init failed"));
		data->philos[i].number = i + 1;
		data->philos[i].l_fork = &(data->forks[i]);
		data->philos[i].r_fork = &(data->forks[\
				(i + 1) % (data->num_of_philos)]);
		if (pthread_mutex_init(&(data->philos[i].mutex_check_starvation), NULL) \
				== FAIL)
			return (error_with_msg("mutex init failed"));
		data->philos[i].data = data;
	}
	return (SUCCESS);
}

static int	init_mutex_for_termination(t_setting *data)
{
	if (pthread_mutex_init(&(data->mutex_flag_finish), NULL) == FAIL)
		return (error_with_msg("mutex init failed"));
	if (pthread_mutex_init(&(data->mutex_error_handling), NULL) == FAIL)
		return (error_with_msg("mutex init failed"));
	return (SUCCESS);
}

int	set_data(t_setting *data, int argc, char **argv)
{
	memset(data, 0, sizeof(t_setting));
	if (set_and_check_args(data, argc, argv) == FAIL)
		return (FAIL);
	if (set_forks_and_philos(data) == FAIL)
		return (FAIL);
	if (init_mutex_for_termination(data) == FAIL)
		return (FAIL);
	return (SUCCESS);
}
