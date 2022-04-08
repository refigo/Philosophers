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

int	fail_with_clearing_data(t_setting *data)
{
	clear_data(data);
	return (FAIL);
}

static int	clear_data_forks(t_setting *data)
{
	int	ret;
	int	i;

	ret = SUCCESS;
	i = -1;
	while (++i < data->num_of_philos)
		if (pthread_mutex_destroy(&(data->forks[i])) != SUCCESS)
			ret = error_with_msg("pthread_mutex_destroy failed in clear forks");
	free(data->forks);
	data->forks = NULL;
	return (ret);
}

static int	clear_data_philos(t_setting *data)
{
	int	ret;
	int	i;

	ret = SUCCESS;
	i = -1;
	while (++i < data->num_of_philos)
		if (pthread_mutex_destroy(&(data->philos[i].mutex_check_starvation)) \
			!= SUCCESS)
			ret = error_with_msg(\
				"pthread_mutex_destroy failed in clear philos");
	free(data->philos);
	data->philos = NULL;
	return (ret);
}

int	clear_data(t_setting *data)
{
	int	ret;

	ret = SUCCESS;
	if (data->forks)
		ret = clear_data_forks(data);
	if (data->philos)
		ret = clear_data_philos(data);
	if (pthread_mutex_destroy(&(data->mutex_flag_finish)) != SUCCESS)
		ret = error_with_msg("pthread_mutex_destroy failed");
	if (pthread_mutex_unlock(&(data->mutex_error_handling)) != SUCCESS)
		ret = error_with_msg("pthread_mutex_unlock failed");
	if (pthread_mutex_destroy(&(data->mutex_error_handling)) != SUCCESS)
		ret = error_with_msg("pthread_mutex_destroy failed");
	return (ret);
}
