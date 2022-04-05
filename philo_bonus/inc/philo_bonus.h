/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 20:19:19 by mgo               #+#    #+#             */
/*   Updated: 2022/04/05 20:19:21 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <semaphore.h>

// to remove
# include <stdio.h>

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

#endif