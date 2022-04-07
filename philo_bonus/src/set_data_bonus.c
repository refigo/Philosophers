/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 09:13:38 by mgo               #+#    #+#             */
/*   Updated: 2022/04/06 09:13:45 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <string.h>

static int	set_and_check_args(t_setting *data, int argc, char **argv)
{
	if (are_args_only_nums(argc, argv) == FALSE)
		return (error_with_msg("not numbers inputed"));
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

static int	set_semaphore(sem_t **sem, const char *file, unsigned int value)
{
	*sem = sem_open(file, O_CREAT, 0644, value);
	if (*sem == SEM_FAILED)
		return (error_with_msg("sem_open failed"));
	return (SUCCESS);
}

static int	set_forks_philos_and_sems(t_setting *data)
{
	int	i;

	data->philos = mgo_calloc(data->num_of_philos, sizeof(t_philo));
	if (data->philos == NULL)
		return (error_with_msg("malloc failed"));
	i = -1;
	while (++i < data->num_of_philos)
	{
		data->philos[i].number = i + 1;
		data->philos[i].data = data;
	}
	data->forks_file = "/sem_forks";
	data->finish_file = "/sem_termination";
	data->print_mutex_file = "/sem_print_mutex";
	data->full_file = "/sem_full";
	if (set_semaphore(&(data->forks), data->forks_file, data->num_of_philos) \
	|| set_semaphore(&(data->finish_sem), data->finish_file, 0) \
	|| set_semaphore(&(data->print_mutex_sem), data->print_mutex_file, 1) \
	|| set_semaphore(&(data->full_sem), data->full_file, 0))
		return (FAIL);
	return (SUCCESS);
}

int	set_data(t_setting *data, int argc, char **argv)
{
	memset(data, 0, sizeof(t_setting));
	if (set_and_check_args(data, argc, argv) == FAIL)
		return (FAIL);
	if (set_forks_philos_and_sems(data))
		return (fail_with_clearing_data(data));
	return (SUCCESS);
}
