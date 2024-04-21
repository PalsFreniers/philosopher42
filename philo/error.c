/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 14:10:34 by tdelage           #+#    #+#             */
/*   Updated: 2024/04/21 19:14:53 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "error.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

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
