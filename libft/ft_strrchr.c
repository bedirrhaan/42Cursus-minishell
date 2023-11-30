/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fibrahim <fibrahim@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:25:48 by fibrahim          #+#    #+#             */
/*   Updated: 2023/11/17 21:03:19 by fibrahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*lastspot;

	lastspot = 0;
	if (c > 127)
		return ((char *)s);
	while (*s)
	{
		if (*s == c)
			lastspot = (char *)s;
		s++;
	}
	if (lastspot)
		return (lastspot);
	if (c == '\0')
		return ((char *)s);
	return (0);
}
