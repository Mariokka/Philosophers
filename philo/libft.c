/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokatova <mokatova@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 17:10:15 by mokatova          #+#    #+#             */
/*   Updated: 2022/04/18 21:05:28 by mokatova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#define MAX_BOUNDARY 922337203685477580
#define MIN_BOUNDARY -922337203685477580

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len] != '\0')
	{
		len++;
	}
	return (len);
}

int	ft_is_digit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_is_space(int c)
{
	if (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

static int	ft_over_boundry(long long int n, char c, int sign)
{
	if ((n * sign) == MIN_BOUNDARY)
		if (c == '8' || c == '9')
			return (0);
	if ((n * sign) < MIN_BOUNDARY - 1)
		return (0);
	if ((n * sign) == MAX_BOUNDARY)
		if (c == '8' || c == '9')
			return (-1);
	if ((n * sign) > MAX_BOUNDARY + 1)
		return (-1);
	return (1);
}

long long int	ft_atoi(char *str)
{
	long long int	n;
	int				sign;
	int				boundry;

	while (ft_is_space(*str))
		str++;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	n = 0;
	while (*str && ft_is_digit(*str))
	{
		boundry = ft_over_boundry(n, *str, sign);
		if (boundry != 1)
			return (boundry);
		n = 10 * n + (*str - '0');
		str++;
	}
	return (n * sign);
}
