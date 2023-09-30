/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getfile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 18:46:22 by nkietwee          #+#    #+#             */
/*   Updated: 2023/10/01 00:43:59 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_getfd_in(t_list *tb_lst)
{
	int		fd_in;
	// t_list *table_list;
	t_table *table;
	t_rdr	*rdr_lst;

	// table_list = main->tb_lst;
	while (tb_lst)
	{
		table = (t_table *)(tb_lst->data);
		while (table->rdr)
		{
			rdr_lst = (t_rdr *)(table->rdr->data);
			if (rdr_lst->type == INFILE)
				fd_in = open(rdr_lst->file, O_RDONLY);
			else if (rdr_lst->type == HEREDOC)
				fd_in = table->exec_data.fd_heredoc;
			if (fd_in == -1)
				ft_prterr(CANNT_OPENIN, rdr_lst->file); // cat: per_di: Permission denied
			// if (fd_in >= 3) // for close file
			// {
			// 	// printf("close\n");
			// 	// close(fd_in);
			// }
			table->rdr = table->rdr->next;
		}
		tb_lst = tb_lst->next;
	}
	// printf("fd_in_getfd : %d\n", fd_in);
	return (fd_in);
}

int	ft_getfd_out(t_list *tb_lst)
{
	int		fd_out;
	// t_list *table_list;
	t_table *table;
	t_rdr	*rdr;

	// table_list = main->tb_lst;
	while (tb_lst)
	{
		table = (t_table *)(tb_lst->data);
		rdr = (t_rdr *)(table->rdr->data);
		if (rdr->type == OUTFILE)
			fd_out = open(rdr->file, O_RDWR | O_CREAT | O_TRUNC , 0644);
		else if (rdr->type == APPEND)
  	      fd_out = open(rdr->file, O_RDWR | O_CREAT | O_APPEND , 0644);
		if (fd_out == -1)
			ft_prterr(CANNT_OPENOUT, "test"); // cat: per_di: Permission denied
		// if (fd_out >= 3)
		// {
		// 	printf("close_outfile\n");
		// 	// close(fd_out);
		// }
		tb_lst = tb_lst->next;
	}
	return (fd_out);
}

/* don't fotget check name of file */
void	ft_getfd(t_list *tb_lst)
{
	int		nbr_infile;
	int		nbr_outfile;
	t_table	*table;
	t_data	*exec_data;

	table = (t_table *)(tb_lst->data);
	exec_data =  &table->exec_data;
	// table->
	nbr_infile = ft_cnt_infile(tb_lst);
	if (nbr_infile == 0) // no infile
		exec_data->fd_in = STDIN_FILENO;
	else
		exec_data->fd_in = ft_getfd_in(tb_lst);
	// printf("fd_in_getfd :  %d\n", exec_data->fd_in);
	nbr_outfile = ft_cnt_outfile(tb_lst);
	if (nbr_outfile == 0) // no outfile
		exec_data->fd_out = STDOUT_FILENO;
	else
		exec_data->fd_out = ft_getfd_out(tb_lst);
	// printf("fd_out_getfd :  %d\n", exec_data->fd_out);
	// dprintf(2, "finish_getfd\n");
}