/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   are_args_only_nums_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 09:41:02 by mgo               #+#    #+#             */
/*   Updated: 2022/04/06 09:41:08 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	is_nums(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if ((str[i] < '0') || ('9' < str[i]))
			return (FALSE);
	}
	return (TRUE);
}

int	are_args_only_nums(int argc, char **argv)
{
	int	i;

	i = 0;
	while (++i < argc)
	{
		if (is_nums(argv[i]) == FALSE)
			return (FALSE);
	}
	return (TRUE);
}
