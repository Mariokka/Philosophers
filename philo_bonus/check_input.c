/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokatova <mokatova@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 20:30:20 by mokatova          #+#    #+#             */
/*   Updated: 2022/04/24 11:46:26 by mokatova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_input(int argc, char **argv)
{
	if (check_argc(argc) == 1)
		return (1);
	if (check_numeric(argv) == 1)
		return (1);
	if (check_over_int(argv) == 1)
		return (1);
	if (check_validity(argv) == 1)
		return (1);
	return (0);
}

int	check_argc(int argc)
{
	if (argc != 5 && argc != 6)
	{
		printf("There should be 4 or 5 arguments\n");
		return (1);
	}
	return (0);
}

int	check_numeric(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
			{
				printf("Only positive numbers are allowed as arguments\n");
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	check_over_int(char **argv)
{
	int				i;
	long long int	nbr;

	i = 1;
	while (argv[i])
	{
		nbr = ft_atoi(argv[i]);
		if (nbr > 2147483647 || ft_strlen(argv[i]) > 18)
		{
			printf("Arguments should be within integer boundaries\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_validity(char **argv)
{
	if (ft_atoi(argv[1]) < 1 || ft_atoi(argv[1]) > 200)
	{
		printf("There should be at least 1, at most - 200 philosophers\n");
		return (1);
	}
	if (ft_atoi(argv[2]) < 60 || ft_atoi(argv[3]) < 60 || ft_atoi(argv[4]) < 60)
	{
		printf("60 ms is the minimum amount of time to do stuff\n");
		return (1);
	}
	if (argv[5])
	{
		if (ft_atoi(argv[5]) <= 0)
		{
			printf("There should be at least one meal\n");
			return (1);
		}
	}
	return (0);
}
