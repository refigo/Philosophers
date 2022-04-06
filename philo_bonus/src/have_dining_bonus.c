/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   have_dining_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 20:26:53 by mgo               #+#    #+#             */
/*   Updated: 2022/04/06 20:26:54 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <unistd.h> // fork()
#include <stdlib.h> // exit()

int	invite_philos(t_setting *data)
{
	int	i;

	pthread_create(&(data->monitor_full_thread), NULL, monitor_full_routine, data);
	set_time_ms(&(data->ms_start_dining));
	i = -1;
	while (++i < data->num_of_philos)
	{
		data->philos[i].ms_eat_last = data->ms_start_dining;
		data->philos[i].philo_pid = fork();
		if (data->philos[i].philo_pid == 0)
		{
			process_philo(&(data->philos[i]));
			exit(TRUE);
		}
		else if (data->philos[i].philo_pid == -1)
			return (FAIL);
	}
	sem_wait(data->termination_sem); // todo: error check
	return (SUCCESS);
}

int	have_dining(t_setting *data)
{
	if (data->num_of_philos == 0)
	{
		printf("Finish: No one is invited!\n");
		return (SUCCESS);
	}
	invite_philos(data);
	//close_when_finished
	return (SUCCESS);
}
