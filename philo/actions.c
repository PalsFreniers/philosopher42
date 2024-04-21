/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 14:10:29 by tdelage           #+#    #+#             */
/*   Updated: 2024/04/21 03:10:21 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

void	take_fork(struct s_philosopher *self)
{
	if (check_forks_ts(self))
	{
		pthread_mutex_lock(self->print_m);
		printf("%llu %llu has taken a fork\n", (get_time() - self->start_time)
			/ 1000, self->id);
		printf("%llu %llu has taken a fork\n", (get_time() - self->start_time)
			/ 1000, self->id);
		pthread_mutex_unlock(self->print_m);
		self->state = FORKED;
		self->thinked = FALSE;
	}
}

void	check_death(struct s_philosopher *self)
{
	t_u64	time;

	time = get_time();
	if ((time - self->last_meal) / 1000 > (self->time_to_die) / 1000)
	{
		pthread_mutex_lock(self->global_m);
		self->parent->dead = self->id;
		self->parent->dead_time = time;
		pthread_mutex_unlock(self->global_m);
	}
}

void	start_eat(struct s_philosopher *self)
{
	pthread_mutex_lock(self->print_m);
	printf("%llu %llu is eating\n", (get_time() - self->start_time) / 1000,
		self->id);
	pthread_mutex_unlock(self->print_m);
	self->state = EATING;
	self->start_eating = get_time();
}

void	start_sleep(struct s_philosopher *self)
{
	pthread_mutex_lock(self->print_m);
	printf("%llu %llu is sleeping\n", (get_time() - self->start_time) / 1000,
		self->id);
	pthread_mutex_unlock(self->print_m);
	self->state = SLEEPING;
	self->start_sleeping = get_time();
}

void	eat(struct s_philosopher *self)
{
	if (get_time() - self->start_eating >= self->time_to_eat)
	{
		pthread_mutex_lock(&(self->fork_left));
		self->left = FALSE;
		pthread_mutex_unlock(&(self->fork_left));
		pthread_mutex_lock(self->fork_right);
		*(self->right) = FALSE;
		pthread_mutex_unlock(self->fork_right);
		self->last_meal = get_time();
		self->state = EATED;
		if (self->passes > 0)
			self->passes--;
		if (self->passes == 0)
		{
			pthread_mutex_lock(self->global_m);
			self->parent->passed++;
			pthread_mutex_unlock(self->global_m);
		}
	}
}
