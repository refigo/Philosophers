/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mgo_putstr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:26:31 by mgo               #+#    #+#             */
/*   Updated: 2022/02/24 13:42:33 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

void	mgo_putstr_fd(char *s, int fd)
{
	if (s)
		write(fd, s, mgo_strlen(s));
}