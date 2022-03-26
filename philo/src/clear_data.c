/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 14:12:10 by mgo               #+#    #+#             */
/*   Updated: 2022/03/26 12:47:58 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

int	fail_with_clearing_data(t_setting *data)
{
	if (data->forks || data->philos)
		clear_data(data);
	return (FAIL);
}

void	clear_data(t_setting *data)
{
	int	i;

	i = -1;
	while (++i < data->num_of_philos)
	{
		pthread_mutex_destroy(&(data->forks[i]));
		pthread_mutex_destroy(&(data->philos[i].mutex_check_starvation));
	}
	pthread_mutex_destroy(&(data->mutex_flag_finish));
	free(data->philos);
	free(data->forks);
}
