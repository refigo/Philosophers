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

int	main(int argc, char **argv)
{
	t_setting	data;

	printf("philo_bonus: hello world!\n");
	if ((argc != 5) && (argc != 6))
		return (error_with_msg("the number of argment is wrong!\n\
Usage: ./philos number_of_philos time_to_die time_to_eat time_to_sleep \
[number_of_times_each_philosophers_must_eat]"));

	set_data(&data, argc, argv);

	test_data(&data);
	return (0);
}
