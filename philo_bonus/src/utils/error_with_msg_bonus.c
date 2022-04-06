/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_with_msg_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 09:18:29 by mgo               #+#    #+#             */
/*   Updated: 2022/04/06 09:18:31 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	error_with_msg(char *msg)
{
	mgo_putstr_fd("Error: ", 2);
	if (msg)
		mgo_putstr_fd(msg, 2);
	mgo_putstr_fd("\n", 2);
	return (FAIL);
}
