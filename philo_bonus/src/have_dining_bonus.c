/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   have_dining_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 20:26:53 by mgo               #+#    #+#             */
/*   Updated: 2022/04/08 09:41:18 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>

static void	close_when_finished(t_setting *data)
{
	int	i;

	i = -1;
	while (++i < data->num_of_philos)
	{
		kill(data->philos[i].philo_pid, SIGKILL);
		waitpid(data->philos[i].philo_pid, NULL, 0);
	}
}

int	create_monitor_threads(t_setting *data)
{
	if (pthread_create(&(data->monitor_full_thread), NULL, \
		monitor_full_routine, data) != SUCCESS
		|| pthread_create(&(data->monitor_error_thread), NULL, \
			monitor_error_routine, data) != SUCCESS)
		return (fail_with_detaching_previous(data));
	pthread_detach(data->monitor_full_thread);
	pthread_detach(data->monitor_error_thread);
	return (SUCCESS);
}

static int	invite_philos(t_setting *data)
{
	int	i;

	if (create_monitor_threads(data) == FAIL)
		return (FAIL);
	set_time_ms(&(data->ms_start_dining));
	i = -1;
	while (++i < data->num_of_philos)
	{
		data->philos[i].ms_eat_last = data->ms_start_dining;
		data->philos[i].philo_pid = fork();
		if (data->philos[i].philo_pid == 0)
		{
			process_philo(&(data->philos[i]));
			exit(SUCCESS);
		}
		else if (data->philos[i].philo_pid == -1)
			return (fail_with_closing(data));
	}
	if (sem_wait(data->finish_sem) == FAIL)
		return (FAIL);
	if (data->is_error_in_philo == TRUE)
		return (FAIL);
	return (SUCCESS);
}

int	have_dining(t_setting *data)
{
	if (data->num_of_philos == 0)
	{
		printf("Finish: No one is invited!\n");
		return (SUCCESS);
	}
	if (invite_philos(data) == FAIL)
		return (FAIL);
	close_when_finished(data);
	return (SUCCESS);
}
