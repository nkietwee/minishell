/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cnt_execute.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 18:33:47 by nkietwee          #+#    #+#             */
/*   Updated: 2023/09/17 01:23:41 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_cntcmd(t_list *table_list)
{
	int	i;
	t_table *table;

	i = 0;
	while (table_list)
	{
		table = (t_table *)(table_list->data);
		if (table->cmd != NULL)
			i++;
		table_list = table_list -> next; // t_lst only
	}
	return (i);
}

// int	ft_cntfile(t_rdr *file)
// {
// 	int	cnt;

// 	cnt = 0;
// 	while (file)
// 	{
// 		cnt++;
// 		file = file->next;
// 	}
// 	return (cnt);
// }
