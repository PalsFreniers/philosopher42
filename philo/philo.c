/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 14:11:43 by tdelage           #+#    #+#             */
/*   Updated: 2024/05/14 04:33:41 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>
#include <unistd.h>

t_u64	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * S2U + tv.tv_usec);
}

static t_bool	check(char *s)
{
	if (!s)
		return (FALSE);
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (FALSE);
		s++;
	}
	return (TRUE);
}

t_bool	global_data_init(int c, char **v, struct s_global_data *data)
{
	int	x;

	x = c;
	while (x)
	{
		if (!check(v[x - 1]))
			return (FALSE);
		--x;
	}
	*data = (struct s_global_data){
		.num = ft_atol(v[0]),
		.passes = -1,
		.time_to_die = ft_atol(v[1]) * 1000,
		.time_to_eat = ft_atol(v[2]) * 1000,
		.time_to_sleep = ft_atol(v[3]) * 1000,
	};
	if (c == 5)
		data->passes = ft_atol(v[4]);
	return (TRUE);
}

void	init_philo(t_u64 i, struct s_global_data *data)
{
	data->philos[i].id = i + 1;
	data->philos[i].print_m = &data->print_m;
	data->philos[i].global_m = &data->global_m;
	data->philos[i].parent = data;
	data->philos[i].passes = data->passes;
	data->philos[i].state = THINK;
	data->philos[i].time_to_die = data->time_to_die;
	data->philos[i].time_to_eat = data->time_to_eat;
	data->philos[i].time_to_sleep = data->time_to_sleep;
	data->philos[i].left = FALSE;
	data->philos[i].num = data->num;
	pthread_mutex_init(&(data->philos[i].fork_left), NULL);
	data->philos[i].right = &(data->philos[(i + 1) % data->num].left);
	data->philos[i].fork_right = &(data->philos[(i + 1) % data->num].fork_left);
}

void	alloc_global_data(struct s_arena *arena, struct s_global_data *data)
{
	t_u64	i;

	data->philos = ft_arena_alloc(arena, data->num
			* sizeof(struct s_philosopher));
	data->thread = ft_arena_alloc(arena, data->num * sizeof(pthread_t));
	data->dead = 0;
	data->dead_time = 0;
	data->passed = 0;
	pthread_mutex_init(&data->print_m, NULL);
	pthread_mutex_init(&data->global_m, NULL);
	i = 0;
	while (i < data->num)
	{
		init_philo(i, data);
		i++;
	}
}
