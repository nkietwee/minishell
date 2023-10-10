/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_dict.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 20:01:48 by nkietwee          #+#    #+#             */
/*   Updated: 2023/10/10 15:21:46 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_lstsize_dict(t_dict *lst)
{
	size_t	count;

	count = 0;
	if (!lst)
		return (0);
	while (lst -> next != NULL)
	{
		lst = lst -> next;
		count++;
	}
	count++;
	return (count);
}
