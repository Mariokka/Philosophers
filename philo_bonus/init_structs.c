/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokatova <mokatova@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 19:01:28 by mokatova          #+#    #+#             */
/*   Updated: 2022/04/27 23:12:31 by mokatova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_struct(t_table **table, char **argv)
{
	sem_t		*forks;

	forks = init_forks(argv);
	init_table(table, forks, argv);
	(*table)->start = timestamp_ms();
}

sem_t	*init_forks(char **argv)
{
	sem_t		*forks;
	int			n_philos;

	n_philos = ft_atoi(argv[1]);
	sem_unlink("forks");
	forks = sem_open("forks", O_CREAT, 644, n_philos);
	return (forks);
}

void	init_table(t_table **table, sem_t *forks, char **argv)
{
	(*table) = malloc(sizeof(t_table));
	(*table)->n_philos = ft_atoi(argv[1]);
	(*table)->forks = forks;
	(*table)->till_dies = ft_atoi(argv[2]);
	(*table)->to_eat = ft_atoi(argv[3]);
	(*table)->to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		(*table)->n_meals = ft_atoi(argv[5]);
	else
		(*table)->n_meals = 999999999;
	(*table)->pids = malloc(sizeof(int) * ft_atoi(argv[1]));
	sem_unlink("eat_sem");
	(*table)->eat_sem = sem_open("eat_sem", O_CREAT, 644, 1);
	sem_unlink("print_sem");
	(*table)->print_sem = sem_open("print_sem", O_CREAT, 644, 1);
	sem_unlink("dead_sem");
	(*table)->dead_sem = sem_open("dead_sem", O_CREAT, 644, 0);
}
