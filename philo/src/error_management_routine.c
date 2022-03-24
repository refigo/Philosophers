/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management_routine.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 12:43:17 by mgo               #+#    #+#             */
/*   Updated: 2022/03/24 13:21:29 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*error_management_routine(void *arg)
{
	t_setting	*data;

	data = arg;

	int	debug;
	debug = pthread_mutex_lock(&(data->mutex_error_management));
	printf("pthread_mutex_lock return value: [%d]\n", debug);

	pthread_mutex_lock(&(data->mutex_flag_finish));
	data->flag_finish = TRUE;
	pthread_mutex_unlock(&(data->mutex_flag_finish));
	printf("Error in thread!\n");
	return (NULL);
}
