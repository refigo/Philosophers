/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   have_dining.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 14:11:26 by mgo               #+#    #+#             */
/*   Updated: 2022/03/19 14:21:30 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	close_when_finished(t_setting *data)
{
	int	i;

	while (data->num_of_philos)
	{
		pthread_mutex_lock(&data->mutex_flag_finish);
		i = -1;
		while (data->flag_finish == TRUE && ++i < data->num_of_philos)
		{
			//pthread_join(data->philos[i].philo_thread, NULL);
			//pthread_join(data->philos[i].monitor_thread, NULL);
			pthread_detach(data->philos[i].philo_thread);
			pthread_detach(data->philos[i].monitor_thread);
		}
		if (data->flag_finish == TRUE)
			break ;
		pthread_mutex_unlock(&data->mutex_flag_finish);
	}
	return (SUCCESS);
}

static int	invite_philos(t_setting *data)
{
	//pthread_t	monitor_thread;
	int	i;

	i = -1;
	while (++i < data->num_of_philos)
	{
		data->philos[i].ms_eat_last = data->ms_start_dining;
		pthread_create(&(data->philos[i].philo_thread), NULL, \
				philo_routine, &(data->philos[i]));
		//pthread_detach(data->philos[i].philo_thread);
		pthread_create(&(data->philos[i].monitor_thread), NULL, \
				monitor_routine, &(data->philos[i]));
		//pthread_detach(data->philos[i].monitor_thread);
	}
	return (SUCCESS);
}

int	have_dining(t_setting *data)
{
	data->ms_start_dining = get_time_ms();
	invite_philos(data);
	close_when_finished(data);
	return (SUCCESS);
}
