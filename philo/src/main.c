/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 09:41:00 by mgo               #+#    #+#             */
/*   Updated: 2022/02/24 17:18:43 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_for_dining(t_setting *data)
{
	t_philo	*philos;
	//malloc_philos_and_forks();
	mgo_calloc((void **)&philos, data->num_of_philos, sizeof(t_philo));
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
