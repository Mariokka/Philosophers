/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stuff_to_do.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokatova <mokatova@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 22:19:03 by mokatova          #+#    #+#             */
/*   Updated: 2022/04/28 00:34:29 by mokatova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philos)
{
	int	is_dead;

	pthread_mutex_lock(&(philos->dead_mutex));
	is_dead = philos->dead;
	pthread_mutex_unlock(&(philos->dead_mutex));
	if (is_dead == 0)
	{
		pthread_mutex_lock(&(philos->table->eat_mutex));
		philos->last_meal = timestamp_ms();
		if (philos->n_meals > 0)
			philos->n_meals--;
		pthread_mutex_unlock(&(philos->table->eat_mutex));
		pthread_mutex_lock(&(philos->table->print_mutex));
		printf("%07lli %d is eating\n", ms_has_passed(philos), philos->id);
		pthread_mutex_unlock(&(philos->table->print_mutex));
		delay(philos->table->to_eat);
	}
}

void	sleep_n_think(t_philo *philos)
{
	int	is_dead;

	pthread_mutex_lock(&(philos->dead_mutex));
	is_dead = philos->dead;
	pthread_mutex_unlock(&(philos->dead_mutex));
	if (is_dead == 0)
	{
		pthread_mutex_lock(&(philos->table->print_mutex));
		printf("%07lli %d is sleeping\n", ms_has_passed(philos), philos->id);
		pthread_mutex_unlock(&(philos->table->print_mutex));
		delay(philos->table->to_sleep);
	}
	pthread_mutex_lock(&(philos->dead_mutex));
	is_dead = philos->dead;
	pthread_mutex_unlock(&(philos->dead_mutex));
	if (is_dead == 0)
	{
		pthread_mutex_lock(&(philos->table->print_mutex));
		printf("%07lli %d is thinking\n", ms_has_passed(philos), philos->id);
		pthread_mutex_unlock(&(philos->table->print_mutex));
	}
}
