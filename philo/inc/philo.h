/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 09:07:25 by mgo               #+#    #+#             */
/*   Updated: 2022/03/24 12:03:41 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>	// to remove?
# include <stdlib.h>
# include <pthread.h>

enum e_bool
{
	FALSE,
	TRUE
};

enum e_valid
{
	SUCCESS,
	FAIL
};

typedef struct s_philo
{
	int					number;
	pthread_t			philo_thread;
	pthread_t			monitor_death_thread;
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		*r_fork;
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
	pthread_mutex_t	*forks;
	long int		ms_start_dining;
	int				num_philos_done;
	pthread_t		monitor_having_eaten_up_thread;
	int				flag_finish;
	pthread_mutex_t	mutex_flag_finish;
}				t_setting;

// set_data.c
int			set_data(t_setting *data, int argc, char **argv);

// have_dining.c
int			have_dining(t_setting *data);

// philo_routine.c
void		*philo_routine(void *arg);

// monitor_routine.c
void		*monitor_death_routine(void *arg);
void		*monitor_having_eaten_up_routine(void *arg);

// clear_data.c
void		clear_data(t_setting *data);

// utils
size_t		mgo_strlen(const char *s);
void		mgo_putstr_fd(char *s, int fd);
int			mgo_atoi(const char *str);
int			error_with_msg(char *msg);
void		*mgo_calloc(size_t count, size_t size);

//long long	get_ms_timeval(struct timeval tv);
//long int	get_time_ms(void);
long int	set_time_ms(long int *dest);

void		print_philo_status(t_philo *philo, char *status);
void		print_philo_died(t_philo *philo, long int ms_now);

// test_philo.c
void	test_overall(t_setting *data);
void	test_setting(t_setting *data);
void	test_philos(t_setting *data);
// to remove

#endif
