/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokatova <mokatova@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 19:01:28 by mokatova          #+#    #+#             */
/*   Updated: 2022/04/28 00:00:43 by mokatova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_struct(t_philo **philos, char **argv)
{
	t_table		*table;
	t_fork		*forks;

	table = NULL;
	forks = init_forks(argv);
	init_table(&table, forks, argv);
	init_philos(argv, philos, table);
	(*philos)->table->start = timestamp_ms();
}

t_fork	*init_forks(char **argv)
{
	int			i;
	t_fork		*forks;
	int			n_philos;

	n_philos = ft_atoi(argv[1]);
	forks = malloc(sizeof(t_fork) * n_philos);
	i = 0;
	while (i < n_philos)
	{
		pthread_mutex_init(&(forks[i].fork_mutex), NULL);
		pthread_mutex_lock(&(forks[i].fork_mutex));
		forks[i].last_eater = 0;
		pthread_mutex_unlock(&(forks[i].fork_mutex));
		i++;
	}
	return (forks);
}

void	init_table(t_table **table, t_fork *forks, char **argv)
{
	(*table) = malloc(sizeof(t_table));
	(*table)->n_philos = ft_atoi(argv[1]);
	(*table)->forks = forks;
	(*table)->till_dies = ft_atoi(argv[2]);
	(*table)->to_eat = ft_atoi(argv[3]);
	(*table)->to_sleep = ft_atoi(argv[4]);
	(*table)->start = 0;
	pthread_mutex_init(&((*table)->eat_mutex), NULL);
	pthread_mutex_init(&((*table)->print_mutex), NULL);
}

void	init_philos(char **argv, t_philo **philos, t_table *table)
{
	int	i;

	*philos = malloc(sizeof(t_philo) * table->n_philos);
	i = 0;
	while (i < table->n_philos)
	{
		(*philos + i)->id = i + 1;
		(*philos + i)->dead = 0;
		if (argv[5])
			(*philos + i)->n_meals = ft_atoi(argv[5]);
		else
			(*philos + i)->n_meals = 999999999;
		(*philos + i)->table = table;
		(*philos + i)->last_meal = timestamp_ms();
		pthread_mutex_init(&((*philos + i)->dead_mutex), NULL);
		i++;
	}
}
