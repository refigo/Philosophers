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

# define EPSILON 300

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
	pid_t				philo_pid;
	pthread_t			monitor_death_thread;
	long int			ms_eat_last;
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
	sem_t			*forks;
	char			*forks_file;
	long int		ms_start_dining;
	pthread_t		monitor_full_thread;

	sem_t			*finish_sem;
	char			*finish_file;
	sem_t			*print_mutex_sem;
	char			*print_mutex_file;
	sem_t			*full_sem;
	char			*full_file;
	pthread_t		monitor_error_thread;
	sem_t			*error_sem;
	char			*error_file;
	int				is_error_in_philo;
}				t_setting;

// set_data_bonus.c
int			set_data(t_setting *data, int argc, char **argv);

// have_dining_bonus.c
int			have_dining(t_setting *data);

// process_philo_bonus.c
void		process_philo(t_philo *philo);

// monitor_routine_bonus.c
void		*monitor_full_routine(void *arg);
void		*monitor_death_routine(void *arg);
void		*monitor_error_routine(void *arg);

// clear_data_bonus.c
int			clear_data(t_setting *data);

// fail.c
int			fail_with_clearing_data(t_setting *data);
int			fail_with_closing(t_setting *data);
int			fail_with_detaching_previous(t_setting *data);

// utils
int			are_args_only_nums(int argc, char **argv);
int			mgo_atoi(const char *str);
void		*mgo_calloc(size_t count, size_t size);
void		mgo_putstr_fd(char *s, int fd);
size_t		mgo_strlen(const char *s);
int			error_with_msg(char *msg);
int			set_time_ms(long int *dest);
int			sleep_shortly_ms(long int ms_sleep);
int			print_philo_died(t_philo *philo, long int ms_now);
int			print_philo_status(t_philo *philo, char *status);

// test
void		test_data(t_setting *data);

#endif