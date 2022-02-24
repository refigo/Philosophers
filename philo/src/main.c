/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 09:41:00 by mgo               #+#    #+#             */
/*   Updated: 2022/02/24 13:34:58 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



int	return_error_with_msg(char *msg)
{
	if (msg)
		mgo_putstr_fd(msg, 2);
	return (1);
}

int	get_data(t_setting *data, int argc, char **argv)
{

	(void)data;
	(void)argc;
	(void)argv;
	return (TRUE);
}

#include <string.h>
int	set_data(t_setting *data, int argc, char **argv)
{
	memset(data, 0, sizeof(t_setting));

	get_data(data, argc, argv);


	test_setting(data);
	(void)argc;
	(void)argv;
	return (TRUE);
}

int	main(int argc, char **argv)
{
	t_setting	data;

	if (argc != 5 && argc != 6)
		return (1);
	if (!set_data(&data, argc, argv))
		return (1);
	//init_data();
	//have_dining();
	//clear_data();

	return (0);
}
