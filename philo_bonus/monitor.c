/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokatova <mokatova@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 20:02:18 by mokatova          #+#    #+#             */
/*   Updated: 2022/04/28 15:51:50 by mokatova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_deaths(void *arg)
{
	t_table	*table;
	int		n_meals;
	int		passed;

	table = (t_table *)arg;
	n_meals = -1;
	while (n_meals != 0)
	{
		n_meals = 0;
		has_sm_died(table, &n_meals, &passed);
		if (passed >= table->till_dies)
		{
			we_have_a_situation(table);
			return (NULL);
		}
	}
	delay(table->till_dies);
	sem_post(table->dead_sem);
	return (NULL);
}

void	has_sm_died(t_table *table, int *n_meals, int *passed)
{
	sem_wait(table->eat_sem);
	(*n_meals) += table->n_meals;
	(*passed) = (int)(timestamp_ms() - (table->last_meal));
	sem_post(table->eat_sem);
}

void	we_have_a_situation(t_table *table)
{
	sem_wait(table->print_sem);
	printf("%07lli %d died\n", ms_has_passed(table), table->id);
	sem_post(table->dead_sem);
}
