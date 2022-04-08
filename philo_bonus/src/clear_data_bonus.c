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

int	clear_data(t_setting *data)
{
	int	ret;

	ret = SUCCESS;
	if (sem_unlink(data->forks_file) == FAIL)
		ret = error_with_msg("sem_unlink failed");
	if (sem_unlink(data->finish_file) == FAIL)
		ret = error_with_msg("sem_unlink failed");
	if (sem_unlink(data->print_mutex_file) == FAIL)
		ret = error_with_msg("sem_unlink failed");
	if (sem_unlink(data->full_file) == FAIL)
		ret = error_with_msg("sem_unlink failed");
	if (sem_unlink(data->error_file) == FAIL)
		ret = error_with_msg("sem_unlink failed");
	if (data->philos)
		free(data->philos);
	data->philos = NULL;
	return (ret);
}
