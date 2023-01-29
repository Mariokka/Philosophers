/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mokatova <mokatova@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 18:14:52 by mokatova          #+#    #+#             */
/*   Updated: 2022/04/28 00:28:23 by mokatova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef pthread_mutex_t	t_mutex;

typedef struct s_fork
{
	t_mutex			fork_mutex;
	int				last_eater;
}	t_fork;

typedef struct s_table
{
	unsigned long long		start;
	long					to_eat;
	long					to_sleep;
	long					till_dies;
	long					n_philos;
	t_fork					*forks;
	t_mutex					eat_mutex;
	t_mutex					print_mutex;

}	t_table;

typedef struct s_philo
{
	pthread_t				thread;
	int						id;
	int						n_meals;
	unsigned long long		last_meal;
	t_table					*table;
	int						dead;
	t_mutex					dead_mutex;
}	t_philo;

/////main.c
void					free_structs(t_philo *philos, int n_philos);
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
unsigned long long		ms_has_passed(t_philo *philo);
/////init_structs.c
void					init_struct(t_philo **philos, char **argv);
t_fork					*init_forks(char **argv);
void					init_table(t_table **table, t_fork *fork, char **argv);
void					init_philos(char **argv, t_philo **philos,
							t_table *table);
/////monitor.c
void					*monitor_deaths(void *arg);
void					has_sm_died(t_philo *philos, int i, int *n_meals,
							int *passed);
void					we_have_a_situation(t_philo *philos, int i);
void					finish_em(t_philo *philos);
/////case_of_one.c
void					loner_life(t_philo *philos, pthread_t *monitor);
void					*pick_n_die(void *arg);
/////start_threads.c
void					start_threads(int n_philos, t_philo *philos);
void					*life_cycle(void *arg);
void					pick_your_fork(t_philo *philos, int *forks);
void					last_eater(t_philo *philos, int *is_dead, int *last,
							int *forks);
void					do_your_thing(t_philo *philos, int *forks);
/////stuff_to_do.c
void					eat(t_philo *philos);
void					sleep_n_think(t_philo *philos);

#endif
