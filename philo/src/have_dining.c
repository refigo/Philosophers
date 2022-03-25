/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   have_dining.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 14:11:26 by mgo               #+#    #+#             */
/*   Updated: 2022/03/25 13:37:30 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	close_when_finished(t_setting *data)
{
	int	i;

	i = -1;
	while (++i < data->num_of_philos)
	{
		pthread_join(data->philos[i].philo_thread, NULL);
		pthread_join(data->philos[i].monitor_death_thread, NULL);
	}
	pthread_join(data->monitor_having_eaten_up_thread, NULL);
	return (SUCCESS);
}

static int	invite_philos(t_setting *data)
{
	int	i;

	pthread_mutex_lock(&(data->mutex_error_management));
	i = -1;
	while (++i < data->num_of_philos)
	{
		data->philos[i].ms_eat_last = data->ms_start_dining;
		if (pthread_create(&(data->philos[i].philo_thread), NULL, \
				philo_routine, &(data->philos[i])) != SUCCESS)
			return (error_with_msg("pthread_create failed"));
		if (pthread_create(&(data->philos[i].monitor_death_thread), NULL, \
				monitor_death_routine, &(data->philos[i])) != SUCCESS)
			return (error_with_msg("pthread_create failed"));
	}
	if (pthread_create(&(data->monitor_having_eaten_up_thread), NULL, \
			monitor_having_eaten_up_routine, data) != SUCCESS)
		return (error_with_msg("pthread_create failed"));
	if (pthread_create(&(data->error_management_thread), NULL, \
			error_management_routine, data) != SUCCESS)
		return (error_with_msg("pthread_create failed"));
	pthread_detach(data->error_management_thread);
	return (SUCCESS);
}

int	have_dining(t_setting *data)
{
	//data->ms_start_dining = get_time_ms();
	set_time_ms(&(data->ms_start_dining));
	if (invite_philos(data) == FAIL)
		return (FAIL);
	close_when_finished(data);
	return (SUCCESS);
}
