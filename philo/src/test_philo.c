/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 12:04:10 by mgo               #+#    #+#             */
/*   Updated: 2022/02/24 12:07:05 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	test_setting(t_setting *data)
{
	printf("num_of_philos: [%d]\n", data->num_of_philos);
	printf("time_to_die: [%d]\n", data->time_to_die);
	printf("time_to_eat: [%d]\n", data->time_to_eat);
	printf("time_to_sleep: [%d]\n", data->time_to_sleep);
	printf("num_of_times_each_must_eat: [%d]\n", data->num_of_times_each_must_eat);

}
