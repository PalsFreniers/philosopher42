/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 14:11:37 by tdelage           #+#    #+#             */
/*   Updated: 2024/04/21 19:15:41 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "philo.h"
#include <unistd.h>

t_bool	check_forks_ts(struct s_philosopher *self)
{
	t_bool	ret;

	ret = TRUE;
	pthread_mutex_lock(&(self->fork_left));
	if (!self->left)
		self->left = TRUE;
	else
		ret = FALSE;
	pthread_mutex_unlock(&(self->fork_left));
	if (!ret)
		return (ret);
	pthread_mutex_lock(self->fork_right);
	if (!(*(self->right)))
		*(self->right) = TRUE;
	else
		ret = FALSE;
	pthread_mutex_unlock(self->fork_right);
	if (!ret)
	{
		pthread_mutex_lock(&(self->fork_left));
		self->left = FALSE;
		pthread_mutex_unlock(&(self->fork_left));
	}
	return (ret);
}

void	manage_state(struct s_philosopher *self)
{
	if (self->state == THINK)
	{
		take_fork(self);
		if (self->state != FORKED)
		{
			if (!self->thinked)
			{
				pthread_mutex_lock(self->print_m);
				printf("%llu %llu is thinking\n", (get_time()
						- self->start_time) / 1000, self->id);
				pthread_mutex_unlock(self->print_m);
				self->thinked = TRUE;
			}
		}
	}
	else if (self->state == FORKED)
		start_eat(self);
	else if (self->state == EATING)
		eat(self);
	else if (self->state == EATED)
		start_sleep(self);
	else if (self->state == SLEEPING)
		if (get_time() - self->start_sleeping >= self->time_to_sleep)
			slp(self);
}

void	*philo(struct s_philosopher *self)
{
	if (self->id % 2 == 0)
		usleep(self->time_to_eat);
	self->last_meal = self->start_time;
	while (TRUE)
	{
		pthread_mutex_lock(self->global_m);
		if (self->parent->dead || self->parent->passed == self->parent->num)
		{
			pthread_mutex_unlock(self->global_m);
			break ;
		}
		pthread_mutex_unlock(self->global_m);
		manage_state(self);
		check_death(self);
		usleep(100);
	}
	return (NULL);
}

void	threads(struct s_global_data *data)
{
	t_u64	i;

	i = 0;
	data->start_time = get_time();
	while (i < data->num)
	{
		data->philos[i].start_time = data->start_time;
		pthread_create(&(data->thread[i]), NULL, (t_pthread_routine)philo,
			&(data->philos[i]));
		i++;
	}
	i = 0;
	while (i < data->num)
	{
		pthread_join(data->thread[i], NULL);
		i++;
	}
	if (data->dead != 0)
		printf("%llu %llu died\n", (data->dead_time - data->start_time) / 1000,
			data->dead);
}

int	main(int c, char **v)
{
	struct s_global_data	data;
	t_u64					size;
	struct s_arena			arena;

	if (c < 5)
		error(v[0], 1, "not enought arguments");
	if (c > 6)
		error(v[0], 2, "too much arguments");
	if (!global_data_init(c - 1, v + 1, &data))
		error(v[0], 3, "error during argument parsing");
	size = data.num * sizeof(struct s_philosopher) + data.num
		* sizeof(pthread_t) + 4;
	arena = ft_arena_create(size);
	if (!arena.ptr)
		return (1);
	alloc_global_data(&arena, &data);
	threads(&data);
	ft_arena_destroy(&arena);
	pthread_mutex_destroy(&data.print_m);
	pthread_mutex_destroy(&data.global_m);
	return (0);
}
