/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling_routine.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 15:51:36 by mgo               #+#    #+#             */
/*   Updated: 2022/03/25 16:06:26 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

void	*error_handling_routine(void *arg)
{
	t_setting	*data;

	data = arg;
	pthread_mutex_lock(&(data->mutex_error_handling));
	pthread_mutex_lock(&(data->mutex_flag_finish));
	data->flag_finish = TRUE;
	pthread_mutex_unlock(&(data->mutex_flag_finish));
	printf("Activate error handling in a thread.\n");
	return (NULL);
}
