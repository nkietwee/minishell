/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_insert.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamwayk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 14:50:11 by nkietwee          #+#    #+#             */
/*   Updated: 2023/10/04 12:36:42 by pnamwayk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_insert(t_dict **lst, t_dict *new, int index)
{
	t_dict *tmp_head;
	t_dict *tmp;
	int	i;

	i = 0;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	tmp_head = *lst;
	while ((*lst))
	{
		(*lst) = (*lst)->next;
		if (i == index)
		{
			(*lst)->next = new;
			new->next;
		}
		i++;
	}
	// (*lst)->next = new;
	(*lst) = tmp;
}

int	main(int ac, char **av, char **env)
{
	t_dict *dict;

	// dict = ft_
}
