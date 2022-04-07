/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_data_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 20:27:45 by mgo               #+#    #+#             */
/*   Updated: 2022/04/07 20:27:47 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <stdlib.h>

void	clear_data(t_setting *data)
{
	sem_unlink(data->forks_file);
	sem_unlink(data->termination_file);
	sem_unlink(data->print_mutex_file);
	sem_unlink(data->full_file);
	if (data->philos)
		free(data->philos);
	data->philos = NULL;
}
