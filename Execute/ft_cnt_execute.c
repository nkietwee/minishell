/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cnt_execute.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 18:33:47 by nkietwee          #+#    #+#             */
/*   Updated: 2023/09/29 02:46:47 by nkietwee         ###   ########.fr       */
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
	// printf("ft_cnt_cmd\n");
	while (table_list)
	{
		table = (t_table *)(table_list->data);
		if (table->cmd[0] != NULL)
		{
			// printf("cmd_ : %s\n", table->cmd[0]);
			i++;
		}
		table_list = table_list->next; // t_lst only
	}
	return (i);
}

int	ft_cnt_infile(t_list *table_list)
{
	int	i;
	t_table *table;
	t_rdr	*rdr;

	i = 0;
	while (table_list)
	{
		table = (t_table *)(table_list->data);
		if (table->rdr)
		{
			rdr = (t_rdr *)(table->rdr->data);
			if (rdr->type == INFILE && rdr)
				i++;
		}
		table_list = table_list->next;
	}
	return (i);
}

int	ft_cnt_outfile(t_list *table_list)
{
	int	i;
	t_table *table;
	t_rdr	*rdr;

	i = 0;
	while (table_list)
	{
		table = (t_table *)(table_list->data);
		if (table->rdr)
		{
			rdr = (t_rdr *)(table->rdr->data);
			if (rdr->type == OUTFILE || rdr->type == APPEND)
				i++;
		}
		table_list = table_list->next;
	}
	return (i);
}

void	ft_countexec(t_list *tb_lst)
{
	t_table	*table;
	t_data	data_exec;

	table = (t_table *)(tb_lst->data);
	data_exec = (t_data )(table->exec_data);
	printf("count_exec\n");


	data_exec.nbr_heredoc = ft_cnt_heredoc(tb_lst);
	printf("nbr_heredoc : %d\n", data_exec.nbr_heredoc);
	data_exec.nbr_cmd = ft_cntcmd(tb_lst);

}