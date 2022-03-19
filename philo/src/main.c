/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 09:41:00 by mgo               #+#    #+#             */
/*   Updated: 2022/03/19 13:45:42 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_finished(t_setting *data)
{
	int	ret;

	pthread_mutex_lock(&data->mutex_flag_finish);
	if (data->flag_finish == TRUE)
		ret = TRUE;
	else
		ret = FALSE;
	pthread_mutex_unlock(&data->mutex_flag_finish);
	return (ret);
}

static void	have_dining(t_setting *data)
{
	//pthread_t	monitor_thread;
	int	i;

	data->ms_start_dining = get_time_ms();
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
}

static void	clear_data(t_setting *data)
{
	int	i;

	i = -1;
	while (++i < data->num_of_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].mutex_check_starvation);
	}
	pthread_mutex_destroy(&data->mutex_flag_finish);
	free(data->philos);
	free(data->forks);
}

int	main(int argc, char **argv)
{
	t_setting	data;

	if ((argc != 5) && (argc != 6))
		return (error_with_msg("the number of args wrong!"));
	if (set_data(&data, argc, argv) == FAIL)
		return (FAIL);
	have_dining(&data);
	//test_overall(&data);
	clear_data(&data);
	//system("leaks philo");
	return (SUCCESS);
}
//error exception with free all???
