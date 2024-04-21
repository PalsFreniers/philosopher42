/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 14:11:47 by tdelage           #+#    #+#             */
/*   Updated: 2024/04/21 19:15:21 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include "lib.h"
# include "types.h"
# include <pthread.h>
# include <stdio.h>
# define S2U 1000000

typedef void				*(*t_pthread_routine)(void *);

enum						e_philo_states
{
	THINK,
	FORKED,
	EATING,
	EATED,
	SLEEPING,
};

struct						s_philosopher;

struct						s_global_data
{
	t_u64					time_to_die;
	t_u64					time_to_eat;
	t_u64					time_to_sleep;
	t_i64					passes;
	t_u64					num;
	t_u64					start_time;
	pthread_t				*thread;
	struct s_philosopher	*philos;
	t_u64					dead;
	t_u64					dead_time;
	pthread_mutex_t			print_m;
	pthread_mutex_t			global_m;
	t_u64					passed;
};

struct						s_philosopher
{
	t_u64					id;
	struct s_global_data	*parent;
	pthread_mutex_t			fork_left;
	t_bool					left;
	pthread_mutex_t			*fork_right;
	t_bool					*right;
	pthread_mutex_t			*print_m;
	pthread_mutex_t			*global_m;
	t_u64					start_time;
	t_u64					start_eating;
	t_u64					start_sleeping;
	t_i64					passes;
	enum e_philo_states		state;
	t_u64					time_to_die;
	t_u64					time_to_eat;
	t_u64					time_to_sleep;
	t_u64					num;
	t_u64					last_meal;
	t_bool					thinked;
};

t_u64						get_time(void);
t_bool						global_data_init(int c, char **v,
								struct s_global_data *data);
void						init_philo(t_u64 i, struct s_global_data *data);
void						alloc_global_data(struct s_arena *arena,
								struct s_global_data *data);
void						take_fork(struct s_philosopher *self);
void						eat(struct s_philosopher *self);
void						start_sleep(struct s_philosopher *self);
void						start_eat(struct s_philosopher *self);
void						check_death(struct s_philosopher *self);
t_bool						check_forks_ts(struct s_philosopher *self);
void						slp(struct s_philosopher *self);

#endif // PHILO_H
