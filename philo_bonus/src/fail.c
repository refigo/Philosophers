/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fail.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 21:57:07 by mgo               #+#    #+#             */
/*   Updated: 2022/04/08 09:38:43 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <signal.h>
#include <sys/wait.h>

int	fail_with_clearing_data(t_setting *data)
{
	clear_data(data);
	return (FAIL);
}

int	fail_with_closing(t_setting *data)
{
	int	i;

	i = 0;
	while ((data->philos[i].philo_pid != 0) \
		&& (data->philos[i].philo_pid != -1) \
		&& (i < data->num_of_philos))
	{
		if (kill(data->philos[i].philo_pid, SIGKILL) == FAIL)
			error_with_msg("kill failed");
		if (waitpid(data->philos[i].philo_pid, NULL, 0) == FAIL)
			error_with_msg("waitpid failed");
		i++;
	}
	return (FAIL);
}

int	fail_with_detaching_previous(t_setting *data)
{
	if (data->monitor_full_thread)
		if (pthread_detach(data->monitor_full_thread) != SUCCESS)
			error_with_msg("pthread_detach failed");
	return (FAIL);
}
