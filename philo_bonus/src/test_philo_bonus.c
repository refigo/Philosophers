/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_philo_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 09:14:02 by mgo               #+#    #+#             */
/*   Updated: 2022/04/06 09:18:22 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	test_data(t_setting *data)
{
	printf("--- Start test_set_data\n");

	printf("num_of_philos: [%d]\n", data->num_of_philos);
	printf("time_to_die: [%d]\n", data->time_to_die);
	printf("time_to_eat: [%d]\n", data->time_to_eat);
	printf("time_to_sleep: [%d]\n", data->time_to_sleep);
	printf("num_of_times_each_must_eat: [%d]\n", data->num_of_times_each_must_eat);

	printf("data->philos: [%p]\n", data->philos);
	printf("data->forks: [%p]\n", data->forks);
	printf("data->termination_sem: [%p]\n", data->termination_sem);
	printf("data->print_mutex_sem: [%p]\n", data->print_mutex_sem);
	printf("data->full_sem: [%p]\n", data->full_sem);

	printf("--- Done test_set_data\n");
}

/*

typedef struct s_philo
{
	int					number;
	pthread_t			philo_thread;
	long int			ms_eat_last;
	pthread_mutex_t		mutex_check_starvation;
	int					num_eat;
	struct s_setting	*data;
}				t_philo;

typedef struct s_setting
{
	int				num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_times_each_must_eat;
	t_philo			*philos;
	sem_t			forks;
}				t_setting;

*/
