/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 23:25:20 by mgo               #+#    #+#             */
/*   Updated: 2022/04/02 23:25:44 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	error_with_usage_msg(void)
{
	return (error_with_msg("the number of argment is wrong!\n\
Usage: ./philos_bonus number_of_philos time_to_die time_to_eat time_to_sleep \
[number_of_times_each_philosophers_must_eat]"));
}

int	main(int argc, char **argv)
{
	t_setting	data;

	if ((argc != 5) && (argc != 6))
		return (error_with_usage_msg());
	if (set_data(&data, argc, argv) == FAIL)
		return (FAIL);
	if (have_dining(&data) == FAIL)
		return (fail_with_clearing_data(&data));
	clear_data(&data);
	return (SUCCESS);
}
