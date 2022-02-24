/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 09:41:00 by mgo               #+#    #+#             */
/*   Updated: 2022/02/24 14:26:37 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



int	error_with_msg(char *msg)
{
	mgo_putstr_fd("Error: ", 2);
	if (msg)
		mgo_putstr_fd(msg, 2);
	mgo_putstr_fd("\n", 2);
	return (FALSE);
}

void	get_data(t_setting *data, int argc, char **argv)
{
	data->num_of_philos = mgo_atoi(argv[1]);
	data->time_to_die = mgo_atoi(argv[2]);
	data->time_to_eat = mgo_atoi(argv[3]);
	data->time_to_sleep = mgo_atoi(argv[4]);
	if (argc == 6)
		data->num_of_times_each_must_eat = mgo_atoi(argv[5]);
}

int	check_data(t_setting *data, int argc)
{
	if (data->num_of_philos < 0)
		return (error_with_msg("number_of_philosophers"));
	if (data->time_to_die < 0)
		return (error_with_msg("time_to_die"));
	if (data->time_to_eat < 0)
		return (error_with_msg("time_to_eat"));
	if (data->time_to_sleep < 0)
		return (error_with_msg("time_to_sleep"));
	if (argc == 6 && data->num_of_times_each_must_eat <= 0)
		return (error_with_msg("number_of_times_each_philosopher_must_eat"));
	return (TRUE);
}

#include <string.h>
int	set_data(t_setting *data, int argc, char **argv)
{
	memset(data, 0, sizeof(t_setting));
	get_data(data, argc, argv);
	if (check_data(data, argc) == FALSE)
		return (FALSE);

	test_setting(data);
	return (TRUE);
}

int	main(int argc, char **argv)
{
	t_setting	data;

	if (argc != 5 && argc != 6)
		return (error_with_msg("the number of args is wrong!"));
	if (set_data(&data, argc, argv) == FALSE)
		return (FALSE);
	//init_for_dining();
	//have_dining();
	//clear_data();

	return (TRUE);
}
