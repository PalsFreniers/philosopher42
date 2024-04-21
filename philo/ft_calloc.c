/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdelage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 16:33:03 by tdelage           #+#    #+#             */
/*   Updated: 2024/04/05 20:20:34 by tdelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "lib.h"
#include <malloc.h>

#define FT_CALLOC_MAX 0xEFFFFFFF

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (size != 0)
		if (nmemb > FT_CALLOC_MAX / size)
			return (NULL);
	if (nmemb != 0)
		if (size > FT_CALLOC_MAX / nmemb)
			return (NULL);
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, nmemb * size);
	return (ptr);
}
