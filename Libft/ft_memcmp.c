/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamwayk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 00:24:45 by ptungbun          #+#    #+#             */
/*   Updated: 2023/10/04 12:36:42 by pnamwayk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*buf_s1;
	const unsigned char	*buf_s2;
	size_t				i;

	if (n != 0)
	{
		buf_s1 = s1;
		buf_s2 = s2;
		i = 0;
		while (i < n)
		{
			if (buf_s1[i] != buf_s2[i])
				return (buf_s1[i] - buf_s2[i]);
			i++;
		}
	}
	return (0);
}
