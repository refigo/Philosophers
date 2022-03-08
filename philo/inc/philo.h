/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 09:07:25 by mgo               #+#    #+#             */
/*   Updated: 2022/03/08 11:59:19 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

//to remove
typedef enum s_bool
{
	FALSE,
	TRUE
}			t_bool;

typedef enum s_valid
{
	SUCCESS,
	FAIL
}			t_valid;

typedef struct s_philo
{
	int					number;
	pthread_t			thread;
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		mutex_for_check;
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
	struct timeval	time_start_dining;
	int				check_for_finish;
}				t_setting;

// set_data.c
int		set_data(t_setting *data, int argc, char **argv);

// utils.c
size_t	mgo_strlen(const char *s);
void	mgo_putstr_fd(char *s, int fd);
int		mgo_atoi(const char *str);
int		error_with_msg(char *msg);
void	*mgo_calloc(size_t count, size_t size);

// test_philo.c
void	test_overall(t_setting *data);
void	test_setting(t_setting *data);
void	test_philos(t_setting *data);

#endif
