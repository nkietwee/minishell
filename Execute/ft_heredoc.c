/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamwayk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 02:36:27 by nkietwee          #+#    #+#             */
/*   Updated: 2023/10/07 17:44:42 by pnamwayk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	t_table *table;
	t_rdr	*rdr;
	t_list *rdr_lst;

	// printf("Entry ft_prt_heredoc\n");
	while (tb_list)
	{
		table = (t_table *)(tb_list->data);
		rdr_lst = table->rdr;
		while (rdr_lst)
		{
			rdr = (t_rdr *)(rdr_lst->data);
			if (rdr->type == HEREDOC)
			{
				// ft_prt_type(rdr->type);
				printf("heredoc__ : %s\n", rdr->file);
			}
			rdr_lst = rdr_lst->next;
		}
		tb_list = tb_list->next;
	}
}

void	ft_heredoc(t_list *tb_lst)
{
	t_table *table;
	t_list	*rdr_lst;
	t_rdr	*rdr;
	char	*tmp;

	while (tb_lst)
	{
		table = (t_table *)(tb_lst->data);
		rdr_lst = table->rdr;
		while (rdr_lst)
		{
			rdr = (t_rdr *)(rdr_lst->data);
			if (rdr->type == HEREDOC)
			{
				rdr->file = ft_strjoinextra(rdr->file, "\n", NONE);
				table->fd_heredoc = open(rdr->file, O_CREAT | O_RDWR | O_TRUNC, 0644);
				dprintf(2, "rdr->file : %s\n" , rdr->file);
				write(STDOUT_FILENO, "> ", 2);
				tmp = get_next_line(STDIN_FILENO);
				while (tmp)
				{
					if (ft_strcmp(tmp, rdr->file) == EXIT_SUCCESS)
						break;
					write(table->fd_heredoc, tmp, ft_strlen(tmp));
					if (tmp)
						free(tmp);
					write(STDOUT_FILENO, "> ", 2);
					tmp = get_next_line(STDIN_FILENO);
				}
				close (table->fd_heredoc);
				dprintf(2,"r->file = %s t->fd_heredoc = %d\n", rdr->file, table->fd_heredoc);
			}
			rdr_lst = rdr_lst->next;
			// dprintf(2, "lst : %s\n", ((t_rdr *)(rdr_lst->data))->file );
		}
		dprintf(2,"table->fd_heredoc = %d\n", table->fd_heredoc);
		tb_lst = tb_lst->next;
	}
}

// int main(int ac, char **av)
// {
// 	// t_data data;
// 	ft_heredoc(ac, av);
// }
