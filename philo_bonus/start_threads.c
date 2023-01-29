/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokatova <mokatova@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 16:14:26 by mokatova          #+#    #+#             */
/*   Updated: 2022/04/28 15:52:07 by mokatova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_threads(int n_philos, t_table *table)
{
	int	pid;
	int	i;

	i = 0;
	pid = 1;
	while (i < n_philos)
	{
		if (pid != 0)
		{
			pid = fork();
			if (pid != 0)
				table->pids[i] = pid;
			if (pid == 0)
				life_cycle(table, i);
		}
		i++;
	}
}

void	*life_cycle(t_table *table, int i)
{
	pthread_t	monitor;

	table->id = i + 1;
	table->last_meal = table->start;
	if (i % 2 != 0)
		delay(table->to_eat);
	pthread_create(&monitor, NULL, &monitor_deaths, table);
	pthread_detach(monitor);
	while (table->n_meals != 0)
		do_your_thing(table);
	return (NULL);
}

void	do_your_thing(t_table *table)
{
	sem_wait(table->forks);
	sem_wait(table->print_sem);
	printf("%07lli %i has taken a fork\n", ms_has_passed(table), table->id);
	sem_post(table->print_sem);
	sem_wait(table->forks);
	sem_wait(table->print_sem);
	printf("%07lli %i has taken a fork\n", ms_has_passed(table), table->id);
	sem_post(table->print_sem);
	eat(table);
	sem_post(table->forks);
	sem_post(table->forks);
	if (table->n_meals != 0)
		sleep_n_think(table);
}
