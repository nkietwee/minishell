/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cnt_execute.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 18:33:47 by nkietwee          #+#    #+#             */
/*   Updated: 2023/09/22 20:58:44 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// int	ft_cnt_heredoc(t_list *tb_list)
int	ft_cnt_heredoc(t_list *tb_list)
{
	int	i;
	t_table *table;
	t_list *rdr_list;
	t_rdr	*rdr;

	i = 0;
	// printf("ft_cnt_heredoc\n");
	while (tb_list)
	{
		table = (t_table *)(tb_list->data);
		rdr_list = table->rdr;
		while (rdr_list)
		{
			rdr = (t_rdr *)(rdr_list->data);
			if (rdr->type == HEREDOC)
			{
				// printf("heredoc : %s\n", rdr->file);
				i++;
			}
			rdr_list = rdr_list->next;
		}
		tb_list = tb_list->next;
	}
	return (i);
}

int	ft_cntcmd(t_list *table_list)
{
	int	i;
	t_table *table;

	i = 0;
	printf("ft_cnt_cmd\n");
	while (table_list)
	{
		table = (t_table *)(table_list->data);
		if (table->cmd[0] != NULL)
		{
			printf("cmd : %s\n", table->cmd[0]);
			i++;
		}
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
