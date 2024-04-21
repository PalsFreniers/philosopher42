/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 14:11:12 by tdelage           #+#    #+#             */
/*   Updated: 2024/04/05 20:15:54 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_H
# define LIB_H

# include "types.h"
# include <stddef.h>
# include <stdlib.h>

struct			s_arena
{
	void		*ptr;
	void		*current;
	size_t		size;
	t_bool		is_free;
};
int				ft_isdigit(int c);
void			*ft_calloc(size_t nmemb, size_t size);
struct s_arena	ft_arena_create(size_t size);
void			ft_arena_destroy(struct s_arena *arena);
void			*ft_arena_alloc(struct s_arena *arena, size_t size);
int				ft_atoi(const char *str);
t_i64			ft_atol(const char *str);
void			*ft_memset(void *s, int c, size_t n);

#endif // LIBFT_H
