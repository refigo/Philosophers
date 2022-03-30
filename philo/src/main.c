/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 09:41:00 by mgo               #+#    #+#             */
/*   Updated: 2022/03/30 19:41:40 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_setting	data;

	if ((argc != 5) && (argc != 6))
		return (error_with_msg("the number of argment is wrong!\n\
Usage: ./philos number_of_philos time_to_die time_to_eat time_to_sleep \
[number_of_times_each_philosophers_must_eat]"));
	if (set_data(&data, argc, argv) == FAIL)
		return (FAIL);
	if (have_dining(&data) == FAIL)
		return (fail_with_clearing_data(&data));
	clear_data(&data);
	return (SUCCESS);
}
