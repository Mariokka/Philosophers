/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokatova <mokatova@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 18:14:49 by mokatova          #+#    #+#             */
/*   Updated: 2022/04/27 23:12:39 by mokatova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table		*table;

	if (check_input(argc, argv) == 1)
		exit(1);
	table = NULL;
	init_struct(&table, argv);
	start_threads(ft_atoi(argv[1]), table);
	if (sem_wait(table->dead_sem) != 0)
	{
		free_struct(table, ft_atoi(argv[1]));
		exit(1);
	}
	free_struct(table, ft_atoi(argv[1]));
	return (0);
}

void	free_struct(t_table *table, int n_philos)
{
	int	j;

	j = 0;
	while (j < n_philos)
		kill(table->pids[j++], SIGKILL);
	j = 0;
	sem_unlink("eat_sem");
	sem_unlink("print_sem");
	sem_unlink("dead_sem");
	sem_unlink("forks");
	sem_close(table->eat_sem);
	sem_close(table->print_sem);
	sem_close(table->dead_sem);
	sem_close(table->forks);
	free(table->pids);
	free(table);
}
