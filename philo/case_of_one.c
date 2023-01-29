/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_of_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokatova <mokatova@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 22:43:55 by mokatova          #+#    #+#             */
/*   Updated: 2022/04/27 23:51:59 by mokatova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	loner_life(t_philo *philos, pthread_t *monitor)
{
	pthread_create(&(philos[0].thread), NULL, &pick_n_die, &(philos[0]));
	usleep(philos[0].table->till_dies * 1000);
	pthread_join(philos[0].thread, NULL);
	pthread_join(*monitor, NULL);
	pthread_mutex_destroy(&(philos->table->forks[0].fork_mutex));
	pthread_mutex_destroy(&(philos[0].dead_mutex));
	free(philos->table->forks);
	free(philos->table);
	free(philos);
}

void	*pick_n_die(void *arg)
{
	t_philo	*philos;
	int		is_dead;

	is_dead = 0;
	philos = (t_philo *)arg;
	pthread_mutex_lock(&(philos->dead_mutex));
	is_dead = philos->dead;
	pthread_mutex_unlock(&(philos->dead_mutex));
	while (is_dead == 0)
	{
		pthread_mutex_lock(&(philos->table->print_mutex));
		printf("%07lli 1 picked a fork\n", ms_has_passed(philos));
		pthread_mutex_unlock(&(philos->table->print_mutex));
		pthread_mutex_lock(&(philos->dead_mutex));
		is_dead = 1;
		pthread_mutex_unlock(&(philos->dead_mutex));
	}
	return (NULL);
}
