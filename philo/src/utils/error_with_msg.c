/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_with_msg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:44:39 by mgo               #+#    #+#             */
/*   Updated: 2022/02/24 17:03:53 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_with_msg(char *msg)
{
	mgo_putstr_fd("Error: ", 2);
	if (msg)
		mgo_putstr_fd(msg, 2);
	mgo_putstr_fd("\n", 2);
	return (NOVALID);
}
