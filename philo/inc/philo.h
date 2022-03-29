/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 09:07:25 by mgo               #+#    #+#             */
/*   Updated: 2022/03/29 11:24:46 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

enum e_bool
{
	FALSE,
	TRUE
};

enum e_valid
{
	FAIL = -1,
	SUCCESS
};

typedef struct s_philo
{
	int					number;
	pthread_t			philo_thread;
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
	pthread_t			monitor_death_thread;
	pthread_t		monitor_having_eaten_up_thread;
	int				num_philos_done;
	int				flag_finish;
	pthread_mutex_t	mutex_flag_finish;
	pthread_t		error_handling_thread;
	pthread_mutex_t	mutex_error_handling;
	int				error_in_thread;
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

// error_handling_routine.c
void		*error_handling_routine(void *arg);

// clear_data.c
void		clear_data(t_setting *data);
int			fail_with_clearing_data(t_setting *data);

// utils
int			are_args_only_nums(int argc, char **argv);
size_t		mgo_strlen(const char *s);
void		mgo_putstr_fd(char *s, int fd);
int			mgo_atoi(const char *str);
int			error_with_msg(char *msg);
void		*mgo_calloc(size_t count, size_t size);
long int	set_time_ms(long int *dest);
int			print_philo_status(t_philo *philo, char *status);
int			print_philo_died(t_philo *philo, long int ms_now);

#endif
