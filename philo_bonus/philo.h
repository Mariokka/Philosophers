/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokatova <mokatova@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 18:14:52 by mokatova          #+#    #+#             */
/*   Updated: 2022/04/28 00:27:45 by mokatova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>

typedef struct s_table
{
	unsigned long long		start;
	unsigned long long		last_meal;
	int						n_meals;
	long					to_eat;
	long					to_sleep;
	long					till_dies;
	long					n_philos;
	int						*pids;
	int						id;
	sem_t					*forks;
	sem_t					*eat_sem;
	sem_t					*print_sem;
	sem_t					*dead_sem;
}	t_table;

/////main.c
void					free_struct(t_table *table, int n_philos);
/////libft.c
int						ft_strlen(char *str);
long long int			ft_atoi(char *str);
/////check_input.c
int						check_input(int argc, char **argv);
int						check_argc(int argc);
int						check_numeric(char **argv);
int						check_over_int(char **argv);
int						check_validity(char **argv);
/////deal_w_time.c
unsigned long long		timestamp_ms(void);
void					delay(int ms);
unsigned long long		ms_has_passed(t_table *table);
/////init_structs.c
void					init_struct(t_table **table, char **argv);
sem_t					*init_forks(char **argv);
void					init_table(t_table **table, sem_t *forks, char **argv);
/////monitor.c
void					*monitor_deaths(void *arg);
void					has_sm_died(t_table *table, int *n_meals, int *passed);
void					we_have_a_situation(t_table *table);
/////start_threads.c
void					start_threads(int n_philos, t_table *table);
void					*life_cycle(t_table *table, int i);
void					do_your_thing(t_table *table);
/////stuff_to_do.c
void					eat(t_table *table);
void					sleep_n_think(t_table *table);

#endif
