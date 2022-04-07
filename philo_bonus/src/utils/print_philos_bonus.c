/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_philos_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 21:17:47 by mgo               #+#    #+#             */
/*   Updated: 2022/04/06 21:17:56 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <stdio.h>

int	print_philo_died(t_philo *philo, long int ms_now)
{
	long int	timestamp_ms;

	timestamp_ms = ms_now - philo->data->ms_start_dining;
	if (printf("%ld %d died\n", timestamp_ms, philo->number) < 0)
		return (FAIL);
	return (SUCCESS);
}

int	print_philo_status(t_philo *philo, char *status)
{
	long int	timestamp_ms;
	int			ret;

	ret = SUCCESS;
	set_time_ms(&timestamp_ms);
	if (sem_wait(philo->data->print_mutex_sem) == FAIL)
		sem_post(philo->data->error_sem);
	timestamp_ms -= philo->data->ms_start_dining;
	if (printf("%ld %d %s\n", timestamp_ms, philo->number, status) < 0)
		ret = FAIL;
	sem_post(philo->data->print_mutex_sem);
	return (ret);
}
