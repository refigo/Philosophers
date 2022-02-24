/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mgo_atoi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 13:22:13 by mgo               #+#    #+#             */
/*   Updated: 2022/02/24 13:29:42 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isdigit(int c)
{
	return (('0' <= c) && (c <= '9'));
}

static int	ft_sign(const char *str, int sign)
{
	if (*str == '+' || *str == '-')
		if (*str == '-')
			sign = -1;
	return (sign);
}

static int	ft_issign(char c)
{
	return (c == '+' || c == '-');
}

static int	ft_isspace(char c)
{
	return (c == '\t' || c == '\n' || c == '\v' \
	|| c == '\f' || c == '\r' || c == ' ');
}

int	mgo_atoi(const char *str)
{
	long long	num;
	int			sign;
	int			count;

	sign = 1;
	num = 0;
	count = 0;
	while (ft_isspace(*str))
		str++;
	if (ft_issign(*str))
		sign = ft_sign(str++, sign);
	while (ft_isdigit(*str))
	{
		num *= 10;
		num += *str - '0';
		count++;
		if (count > 19)
		{
			if (sign == -1)
				return (0);
			return (-1);
		}
		str++;
	}
	return ((int)(sign * num));
}
