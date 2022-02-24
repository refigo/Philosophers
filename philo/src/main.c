/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 09:41:00 by mgo               #+#    #+#             */
/*   Updated: 2022/02/24 17:10:44 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_for_dining(t_setting *data)
{
	//malloc_philos_and_forks();
	//mgo_calloc(1, sizeof(pthread_t));
	//create_philos();
	//init_forks();

	test_setting(data);
	return (TRUE);
}

int	main(int argc, char **argv)
{
	t_setting	data;

	if ((argc != 5) && (argc != 6))
		return (error_with_msg("the number of args wrong!"));
	if (set_data(&data, argc, argv) == NOVALID)
		return (NOVALID);
	init_for_dining(&data);
	//have_dining();
	//clear_data();

	return (VALID);
}
