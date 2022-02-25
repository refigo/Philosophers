/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 12:04:10 by mgo               #+#    #+#             */
/*   Updated: 2022/02/25 12:53:28 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	test_setting(t_setting *data)
{
	printf("----- test t_setting *data\n");

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
