/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 14:12:10 by mgo               #+#    #+#             */
/*   Updated: 2022/03/30 19:38:44 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

#include <stdio.h>

int	fail_with_clearing_data(t_setting *data)
{
	printf("in fail_with_clearing_data\n");
	clear_data(data);
	return (FAIL);
}

static void	clear_data_forks(t_setting *data)
{
	int	i;

	i = -1;
	while (++i < data->num_of_philos)
		pthread_mutex_destroy(&(data->forks[i]));
	free(data->forks);
	data->forks = NULL;
}

static void	clear_data_philos(t_setting *data)
{
	int	i;

	i = -1;
	while (++i < data->num_of_philos)
		pthread_mutex_destroy(&(data->philos[i].mutex_check_starvation));
	free(data->philos);
	data->philos = NULL;
}

void	clear_data(t_setting *data)
{
	if (data->forks)
		clear_data_forks(data);
	if (data->philos)
		clear_data_philos(data);
	pthread_mutex_destroy(&(data->mutex_flag_finish));
	pthread_mutex_destroy(&(data->mutex_error_handling));
}
