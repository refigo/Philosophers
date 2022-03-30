/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   have_dining.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 14:11:26 by mgo               #+#    #+#             */
/*   Updated: 2022/03/30 17:35:01 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

static int	close_when_finished(t_setting *data)
{
	int		i;

	i = -1;
	while (++i < data->num_of_philos)
		pthread_join(data->philos[i].philo_thread, NULL);
	pthread_join(data->monitor_death_thread, NULL);
	pthread_join(data->monitor_having_eaten_up_thread, NULL);
	return (SUCCESS);
}

int	fail_with_detaching(t_setting *data)
{
	int	i;

	i = -1;
	while (++i < data->num_of_philos)
		pthread_detach(data->philos[i].philo_thread);
	pthread_detach(data->monitor_death_thread);
	pthread_detach(data->monitor_having_eaten_up_thread);
	return (FAIL);
}

int	error_with_joining_previous(t_setting *data, int last_index)
{
	int	i;

	pthread_mutex_lock(&(data->mutex_flag_finish));
	data->flag_finish = TRUE;
	pthread_mutex_unlock(&(data->mutex_flag_finish));
	i = -1;
	while (++i < last_index)
		pthread_join(data->philos[i].philo_thread, NULL);
	return (error_with_msg("pthread_create failed"));
}

static int	invite_philos(t_setting *data)
{
	int	i;

	pthread_mutex_lock(&(data->mutex_error_handling));
	i = -1;
	while (++i < data->num_of_philos)
	{
		data->philos[i].ms_eat_last = data->ms_start_dining;
		if (pthread_create(&(data->philos[i].philo_thread), NULL, \
				philo_routine, &(data->philos[i])) != SUCCESS)
			return (error_with_joining_previous(data, i));
	}
	if (pthread_create(&(data->monitor_death_thread), NULL, \
				monitor_death_routine, data) != SUCCESS)
		return (error_with_msg("pthread_create failed"));
	if (pthread_create(&(data->monitor_having_eaten_up_thread), NULL, \
			monitor_having_eaten_up_routine, data) != SUCCESS)
		return (error_with_msg("pthread_create failed"));
	pthread_detach(data->monitor_having_eaten_up_thread);
	if (pthread_create(&(data->error_handling_thread), NULL, \
			error_handling_routine, data) != SUCCESS)
		return (error_with_msg("pthread_create failed"));
	pthread_detach(data->error_handling_thread);
	return (SUCCESS);
}

int	have_dining(t_setting *data)
{
	if (data->num_of_philos == 0)
	{
		printf("Finish: No one is invited!\n");
		return (SUCCESS);
	}
	set_time_ms(&(data->ms_start_dining));
	if (invite_philos(data) == FAIL)
		return (fail_with_detaching(data));
	close_when_finished(data);
	if (data->error_in_thread == TRUE)
		return (FAIL);
	return (SUCCESS);
}
