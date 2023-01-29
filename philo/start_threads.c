/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokatova <mokatova@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 16:14:26 by mokatova          #+#    #+#             */
/*   Updated: 2022/04/28 00:34:43 by mokatova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_threads(int n_philos, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < n_philos)
	{
		pthread_create(&(philos[i].thread), NULL, &life_cycle, &(philos[i]));
		i += 2;
	}
	delay(5);
	i = 1;
	while (i < n_philos)
	{
		pthread_create(&(philos[i].thread), NULL, &life_cycle, &(philos[i]));
		i += 2;
	}
}

void	*life_cycle(void *arg)
{
	t_philo	*philos;
	int		last[2];
	int		left_n_right[2];
	int		is_dead;

	philos = (t_philo *)arg;
	is_dead = 0;
	pick_your_fork(philos, left_n_right);
	is_dead = philos->dead;
	while (is_dead == 0)
	{
		last_eater(philos, &is_dead, last, left_n_right);
		if (last[0] != philos->id && last[1] != philos->id && is_dead == 0)
			do_your_thing(philos, left_n_right);
	}
	return (NULL);
}

void	pick_your_fork(t_philo *philos, int *forks)
{
	if (philos->id != philos->table->n_philos)
	{
		forks[0] = philos->id - 1;
		forks[1] = philos->id;
	}
	else
	{
		forks[0] = 0;
		forks[1] = philos->id - 1;
	}
}

void	last_eater(t_philo *philos, int *is_dead, int *last, int *forks)
{
	pthread_mutex_lock(&(philos->table->forks[forks[0]].fork_mutex));
	last[0] = philos->table->forks[forks[0]].last_eater;
	pthread_mutex_unlock(&(philos->table->forks[forks[0]].fork_mutex));
	pthread_mutex_lock(&(philos->table->forks[forks[1]].fork_mutex));
	last[1] = philos->table->forks[forks[1]].last_eater;
	pthread_mutex_unlock(&(philos->table->forks[forks[1]].fork_mutex));
	pthread_mutex_lock(&(philos->dead_mutex));
	*is_dead = philos->dead;
	pthread_mutex_unlock(&(philos->dead_mutex));
}

void	do_your_thing(t_philo *philos, int *forks)
{
	pthread_mutex_lock(&(philos->table->forks[forks[0]].fork_mutex));
	pthread_mutex_lock(&(philos->table->print_mutex));
	printf("%07lli %i has taken a fork\n", ms_has_passed(philos), philos->id);
	pthread_mutex_unlock(&(philos->table->print_mutex));
	pthread_mutex_lock(&(philos->table->forks[forks[1]].fork_mutex));
	pthread_mutex_lock(&(philos->table->print_mutex));
	printf("%07lli %i has taken a fork\n", ms_has_passed(philos), philos->id);
	pthread_mutex_unlock(&(philos->table->print_mutex));
	eat(philos);
	philos->table->forks[forks[0]].last_eater = philos->id;
	philos->table->forks[forks[1]].last_eater = philos->id;
	pthread_mutex_unlock(&(philos->table->forks[forks[1]].fork_mutex));
	pthread_mutex_unlock(&(philos->table->forks[forks[0]].fork_mutex));
	if (philos->n_meals != 0)
		sleep_n_think(philos);
}
