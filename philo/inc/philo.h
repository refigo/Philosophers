/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 09:07:25 by mgo               #+#    #+#             */
/*   Updated: 2022/02/24 14:26:56 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef enum s_bool
{
	TRUE,
	FALSE
}			t_bool;

typedef struct s_philo
{
	int					name;
	pthread_t			*thread;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	struct timeval		time_eat_last;
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
	pthread_mutex_t	*forks;
	struct timeval	time_start;

}				t_setting;

// utils.c
size_t	mgo_strlen(const char *s);
void	mgo_putstr_fd(char *s, int fd);
int		mgo_atoi(const char *str);

// test_philo.c
void	test_setting(t_setting *data);

#endif
