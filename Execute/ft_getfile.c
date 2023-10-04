/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getfile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamwayk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 18:46:22 by nkietwee          #+#    #+#             */
/*   Updated: 2023/10/05 01:31:27 by pnamwayk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_accessfile(char *file, int type)
{
	int errno;

	errno = 127; // check
	// ft_prt_type(type);
	if (type == HEREDOC || type == OUTFILE || type == APPEND)
		return (EXIT_SUCCESS);
	if (access(file, F_OK) == 0)
	{
		if (access(file, R_OK | F_OK) == -1)
		{
			ft_prterrexec(file, errno, PER_FILE);
			return (EXIT_FAILURE);
		}
	}
	else
	{
		ft_prterrexec(file, errno, NO_FILE);
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_getfd_in(t_list *tb_lst)
{
	int		fd_in;
	// int		i;
	t_table *table;
	t_rdr	*rdr;
	t_list	*rdr_lst;

	// i = 0;
	table = (t_table *)(tb_lst->data);
	rdr_lst = (t_list *)(table->rdr);
	while (rdr_lst)
	{
		rdr = (t_rdr *)(rdr_lst->data);
		if (ft_accessfile(rdr->file, rdr->type) == EXIT_FAILURE)
			return(-1);
		if (rdr->type == INFILE)
			fd_in = open(rdr->file, O_RDONLY);
		else if (rdr->type == HEREDOC)
			fd_in = table->fd_heredoc;
		rdr_lst = rdr_lst->next;
	}
	return (fd_in);



	// while (tb_lst)
	// {
	// 	table = (t_table *)(tb_lst->data);
	// 	while (table->rdr)
	// 	{
	// 		// dprintf(2, "ft_getfd_in\n");
	// 		rdr_lst = (t_rdr *)(table->rdr->data);
	// 		if (ft_accessfile(rdr_lst->file, rdr_lst->type) == EXIT_FAILURE)
	// 		{
	// 			// dprintf(2, "exit_fdin\n");
	// 			return(-1);
	// 		}
	// 		if (rdr_lst->type == INFILE)
	// 			fd_in = open(rdr_lst->file, O_RDONLY);
	// 		else if (rdr_lst->type == HEREDOC)
	// 			fd_in = table->fd_heredoc;
	// 		table->rdr = table->rdr->next;
	// 	}
	// 	tb_lst = tb_lst->next;
	// }
	// dprintf(2, "fd_here_getfd_in : %d\n", fd_in);
	// exit(0);
	// return (fd_in);
}

int	ft_getfd_out(t_list *tb_lst)
{
	int		fd_out;
	t_table *table;
	t_rdr	*rdr_lst;

	while (tb_lst)
	{
		table = (t_table *)(tb_lst->data);
		while (table->rdr)
		{
			rdr_lst = (t_rdr *)(table->rdr->data);
			// dprintf(2, "getfd_out_1\n");
			if (rdr_lst->type == OUTFILE)
			{
				// dprintf(2, "file : %s\n", rdr_lst->file);
				fd_out = open(rdr_lst->file, O_RDWR | O_CREAT | O_TRUNC , 0644);
				// dprintf(2, "fd_out[] : %d\n", fd_out);
			}
			else if (rdr_lst->type == APPEND)
				fd_out = open(rdr_lst->file, O_RDWR | O_CREAT | O_APPEND , 0644);
			// if (ft_accessfile(rdr_lst->file, rdr_lst->type) == EXIT_FAILURE)
			// 	return(-1);
			table->rdr = table->rdr->next;
		}
		tb_lst = tb_lst->next;
	}
	// dprintf(2, "fd_out[] : %d\n", fd_out);
	return (fd_out);
}

/* don't fotget check name of file */
void	ft_getfd(t_minishell *ms, t_list *tb_lst)
{
	// int		nbr_infile;
	// int		nbr_outfile;
	t_table	*table;

	table = (t_table *)(tb_lst->data);
	// table->nbr_infile = ft_cnt_infile(tb_lst);
	if (table->nbr_infile || table->nbr_heredoc) // no infile
		table->fd_in = ft_getfd_in(tb_lst);
	else if (table->i != 0)
		table->fd_in = table->fd_tmp;
	// nbr_outfile = ft_cnt_outfile(tb_lst);
	if (table->nbr_outfile) // no outfile
		table->fd_out = ft_getfd_out(tb_lst);
	else if (table->i != ms->nbr_cmd - 1 && ms->nbr_cmd > 1)
		table->fd_out = table->fd_pipe[1];
	// dprintf(2 , "%d nbr_outfile:  %d fd_in_getfd__ :  %d\n", table->i, nbr_outfile, exec_data->fd_in);
	// dprintf(2 , "%d nbr_outfile:  %d fd_out_getfd__ :  %d\n", table->i, nbr_outfile, exec_data->fd_out);
}
