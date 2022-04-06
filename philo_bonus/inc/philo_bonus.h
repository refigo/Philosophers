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
	pthread_t			monitor_thread;
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

	sem_t			*termination_sem;
	sem_t			*print_mutex_sem;
	sem_t			*full_sem;
	//sem_t			error_sem;
	char			*termination_file;
	char			*print_mutex_file;
	char			*full_file;
	//char			*error_file;
}				t_setting;


// set_data_bonus.c
int	set_data(t_setting *data, int argc, char **argv);

// utils
int	are_args_only_nums(int argc, char **argv);
int	mgo_atoi(const char *str);
void	*mgo_calloc(size_t count, size_t size);
void	mgo_putstr_fd(char *s, int fd);
size_t	mgo_strlen(const char *s);
int	error_with_msg(char *msg);

// test
void	test_data(t_setting *data);

#endif