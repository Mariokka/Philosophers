/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokatova <mokatova@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 18:14:49 by mokatova          #+#    #+#             */
/*   Updated: 2022/04/27 22:12:56 by mokatova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo		*philos;
	pthread_t	monitor;

	if (check_input(argc, argv) == 1)
		return (1);
	philos = NULL;
	init_struct(&philos, argv);
	pthread_create(&monitor, NULL, &monitor_deaths, philos);
	if (ft_atoi(argv[1]) == 1)
		loner_life(philos, &monitor);
	else
	{
		start_threads(ft_atoi(argv[1]), philos);
		pthread_join(monitor, NULL);
		free_structs(philos, ft_atoi(argv[1]));
	}
	return (0);
}

void	free_structs(t_philo *philos, int n_philos)
{
	int	j;

	j = 0;
	while (j < n_philos)
		pthread_join((philos[j++].thread), NULL);
	j = 0;
	while (j < n_philos)
	{
		pthread_mutex_destroy(&(philos->table->forks[j].fork_mutex));
		pthread_mutex_destroy(&(philos[j].dead_mutex));
		j++;
	}
	free(philos->table->forks);
	free(philos->table);
	free(philos);
}
