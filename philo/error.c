/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 14:10:34 by tdelage           #+#    #+#             */
/*   Updated: 2024/05/14 04:32:43 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "philo.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	delete_mtx(struct s_global_data *data)
{
	t_u64	i;

	i = 0;
	while (i < data->num)
	{
		pthread_mutex_destroy(&(data->philos[i].fork_left));
		i++;
	}
}

void	slp(struct s_philosopher *self)
{
	self->state = THINK;
	usleep(500);
}

void	error(char *name, int code, char *err)
{
	printf("[ERROR] %s => %s\n", name, err);
	exit(code);
}
