/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokatova <mokatova@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 20:02:18 by mokatova          #+#    #+#             */
/*   Updated: 2022/04/27 23:56:32 by mokatova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_deaths(void *arg)
{
	t_philo	*philos;
	int		i;
	int		n_meals;
	int		passed;

	philos = (t_philo *)arg;
	i = 0;
	n_meals = -1;
	while (n_meals != 0)
	{
		i = 0;
		n_meals = 0;
		while (i < philos->table->n_philos)
		{
			has_sm_died(philos, i, &n_meals, &passed);
			if (passed >= philos->table->till_dies)
			{
				we_have_a_situation(philos, i);
				return (NULL);
			}
		i++;
		}
	}
	finish_em(philos);
	return (NULL);
}

void	has_sm_died(t_philo *philos, int i, int *n_meals, int *passed)
{
	pthread_mutex_lock(&(philos->table->eat_mutex));
	(*n_meals) += philos[i].n_meals;
	(*passed) = (int)(timestamp_ms() - (philos[i].last_meal));
	pthread_mutex_unlock(&(philos->table->eat_mutex));
}

void	we_have_a_situation(t_philo *philos, int i)
{
	int	j;

	j = 0;
	pthread_mutex_lock(&(philos->table->print_mutex));
	printf("%07lli %d died\n", ms_has_passed(philos), philos[i].id);
	while (j < philos->table->n_philos)
	{
		if ((philos[j].thread) != 0)
		{
			pthread_mutex_lock(&(philos[j].dead_mutex));
			philos[j].dead = 1;
			pthread_mutex_unlock(&(philos[j].dead_mutex));
		}
		j++;
	}
	pthread_mutex_unlock(&(philos->table->print_mutex));
}

void	finish_em(t_philo *philos)
{
	int	j;

	j = 0;
	while (j < philos->table->n_philos)
	{
		if ((philos[j].thread) != 0)
		{
			pthread_mutex_lock(&(philos[j].dead_mutex));
			philos[j].dead = 1;
			pthread_mutex_unlock(&(philos[j].dead_mutex));
		}
		j++;
	}
}
