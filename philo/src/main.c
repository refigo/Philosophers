/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 09:41:00 by mgo               #+#    #+#             */
/*   Updated: 2022/02/25 13:08:29 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	init_for_dining(t_setting *data)
{
	int	i;


	//create_philos();
	i = -1;
	while (++i < data->num_of_philos)
	{

	}

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
