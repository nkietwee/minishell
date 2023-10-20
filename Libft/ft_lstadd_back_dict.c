/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_dict.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 02:09:46 by nkietwee          #+#    #+#             */
/*   Updated: 2023/10/10 15:22:08 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_dict	*ft_lstlast_dict(t_dict *lst)
{
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back_dict(t_dict **lst, t_dict *new)
{
	t_dict	*last;

	if (!lst || !new)
		return ;
	if (*lst)
	{
		last = ft_lstlast_dict(*lst);
		last->next = new;
	}
	else
		*lst = new;
}
