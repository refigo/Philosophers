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

#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
void	clear_data(t_setting *data)
{
	int	i;

	i = -1;
	while (++i < data->num_of_philos)
	{
		kill(data->philos[i].philo_pid, SIGKILL); // check
		//waitpid(data->philos[i].philo_pid, NULL, WNOHANG);
		waitpid(data->philos[i].philo_pid, NULL, 0);
	}

	//sem_close()
	sem_unlink(data->forks_file);
	sem_unlink(data->termination_file);
	sem_unlink(data->print_mutex_file);
	sem_unlink(data->full_file);

	free(data->philos); // todo: check
}

int	main(int argc, char **argv)
{
	t_setting	data;

	printf("philo_bonus: hello world!\n");
	if ((argc != 5) && (argc != 6))
		return (error_with_msg("the number of argment is wrong!\n\
Usage: ./philos_bonus number_of_philos time_to_die time_to_eat time_to_sleep \
[number_of_times_each_philosophers_must_eat]"));
	set_data(&data, argc, argv);
	have_dining(&data);
	clear_data(&data);

	test_data(&data);
	system("leaks philo_bonus");
	return (0);
}
