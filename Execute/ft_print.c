/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:16:03 by nkietwee          #+#    #+#             */
/*   Updated: 2023/10/10 15:18:15 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_prt_type(int type)
{
	if (type == EMPTY)
		dprintf(2, "EMPTY\n");
	else if (type == CMD)
		printf("CMD\n");
	else if (type == ARG)
		printf("ARG\n");
	else if (type == FPATH)
		printf("FPATH\n");
	else if (type == INFILE)
		dprintf(2, "INFILE\n");
	else if (type == OUTFILE)
		dprintf(2, "OUTFILE\n");
	else if (type == HEREDOC)
		dprintf(2, "HEREDOC\n");
	else if (type == PIPE)
		printf("PIPE\n");
	else if (type == APPEND)
		printf("APPEND\n");
}

void	ft_prt_heredoc(t_list *tb_list)
{
	t_table	*table;
	t_rdr	*rdr;
	t_list	*rdr_lst;

	while (tb_list)
	{
		table = (t_table *)(tb_list->data);
		rdr_lst = table->rdr;
		while (rdr_lst)
		{
			rdr = (t_rdr *)(rdr_lst->data);
			if (rdr->type == HEREDOC)
				printf("heredoc__ : %s\n", rdr->file);
			rdr_lst = rdr_lst->next;
		}
		tb_list = tb_list->next;
	}
}
