/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamwayk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 23:21:29 by ptungbun          #+#    #+#             */
/*   Updated: 2023/10/04 12:36:42 by pnamwayk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const char	*buf_s;
	size_t		i;

	buf_s = s;
	i = 0;
	while (i < n)
	{
		if (buf_s[i] == (unsigned char)c)
		{
			return ((void *)(s + i));
		}
		i++;
	}
	return (0);
}
