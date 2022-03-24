/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 09:41:00 by mgo               #+#    #+#             */
/*   Updated: 2022/03/24 11:39:42 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_with_clearing_data(t_setting *data)
{
	clear_data(data);
	return (FAIL);
}

int	main(int argc, char **argv)
{
	t_setting	data;

	if ((argc != 5) && (argc != 6))
		return (error_with_msg("the number of argment is wrong!"));
	if (set_data(&data, argc, argv) == FAIL)
		return (FAIL);
	if (have_dining(&data) == FAIL)
		return (error_with_clearing_data(&data));
	//test_overall(&data);
	clear_data(&data);
	//system("leaks philo");
	return (SUCCESS);
}
//error exception with free all???
