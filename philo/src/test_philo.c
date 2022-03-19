/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 12:04:10 by mgo               #+#    #+#             */
/*   Updated: 2022/03/19 14:25:50 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	test_setting(t_setting *data)
{
	printf("----- test t_setting *data\n");

	printf("data address: [%p]\n", data);
	printf("num_of_philos: [%d]\n", data->num_of_philos);
	printf("time_to_die: [%d]\n", data->time_to_die);
	printf("time_to_eat: [%d]\n", data->time_to_eat);
	printf("time_to_sleep: [%d]\n", data->time_to_sleep);
	printf("num_of_times_each_must_eat: [%d]\n", data->num_of_times_each_must_eat);
	//philos, forks
	printf("philos addr: [%p]\n", data->philos);
	printf("forks addr: [%p]\n", data->forks);

	printf("----- done t_setting *data\n");
}

void	test_philos(t_setting *data)
{
	t_philo	curr_philo;
	int		i;

	printf("----- test t_philo *philos\n");

	i = -1;
	while (++i < data->num_of_philos)
	{
		printf("---- test each philo\n");
		curr_philo = data->philos[i];
		printf("philos[%d].number: [%d]\n", i, curr_philo.number);
		printf("philos[%d].l_fork: [%p]\n", i, curr_philo.l_fork);
		printf("philos[%d].r_fork: [%p]\n", i, curr_philo.r_fork);
		//printf("philos[%d].mutex_for_check: [%p]\n", i, &(curr_philo.mutex_for_check));
		printf("philos[%d].data: [%p]\n", i, curr_philo.data);

		printf("---- done each philo\n");
	}

	printf("----- done t_philo *philos\n");
}

/*
#include <sys/time.h>
void	test_timeval(t_setting *data)
{
	printf("---- test timeval\n");
	printf("time_start_dining.tv_sec: [%ld]\n", data->time_start_dining.tv_sec);
	printf("time_start_dining.tv_usec: [%d]\n", data->time_start_dining.tv_usec);
	printf("ms_start_dining: [%lld]\n", get_ms_timeval(data->time_start_dining));
	printf("----- done timeval\n");
}
*/

void	test_overall(t_setting *data)
{
	test_setting(data);
	test_philos(data);
	//test_timeval(data);
}
