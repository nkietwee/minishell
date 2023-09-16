/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getfile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 18:46:22 by nkietwee          #+#    #+#             */
/*   Updated: 2023/09/17 01:27:36 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_cnt_heredoc(t_list *table_list)
{
	int	i;
	t_table *table;
	t_rdr	*rdr;

	i = 0;
	while (table_list)
	{
		table = (t_table *)(table_list->data);
		rdr = (t_rdr *)(table->rdr->data);
		if (rdr->type == HEREDOC)
			i++;
		table_list = table_list->next;
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
		rdr = (t_rdr *)(table->rdr->data);
		if (rdr->type == INFILE)
			i++;
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
		rdr = (t_rdr *)(table->rdr->data);
		if (rdr->type == OUTFILE || rdr->type == APPEND)
			i++;
		table_list = table_list->next;
	}
	return (i);
}


int	ft_getfd_in(t_minishell *main)
{
	int		fd_in;
	t_list *table_list;
	t_table *table;
	t_rdr	*rdr;

	table_list = main->table;
	while (table_list)
	{
		table = (t_table *)(table_list);
		rdr = (t_rdr *)(table->rdr->data);
		if (rdr->type == INFILE)
			fd_in = open(rdr->file, O_RDONLY);
		else if (rdr->type == HEREDOC)
			fd_in = main->data->fd_heredoc;
		if (fd_in == -1)
			ft_prterr(CANNT_OPENIN); // cat: per_di: Permission denied
		table_list = table_list->next;
	}
	return (fd_in);
}

int	ft_getfd_out(t_minishell *main)
{
	int		fd_out;
	t_list *table_list;
	t_table *table;
	t_rdr	*rdr;

	table_list = main->table;
	while (table_list)
	{
		table = (t_table *)(table_list);
		rdr = (t_rdr *)(table->rdr->data);
		if (rdr->type == OUTFILE)
			fd_out = open(rdr->file, O_RDWR | O_CREAT | O_TRUNC , 0644);
		else if (rdr->type == APPEND)
  	      fd_out = open(rdr->file, O_RDWR | O_CREAT | O_APPEND , 0644);
		if (fd_out == -1)
			ft_prterr(CANNT_OPENIN); // cat: per_di: Permission denied
		table_list = table_list->next;
	}
	return (fd_out);
}


void	ft_getfd(t_minishell *main)
{
	int		nbr_infile;
	int		nbr_outfile;
	// t_table	*table;

	// table = (t_table *)(main->table->data);
	nbr_infile = ft_cnt_infile(main->table);
	if (nbr_infile == 0) // no infile
		main->data->fd_in = STDIN_FILENO;
	else
		main->data->fd_in = ft_getfd_in(main);
	nbr_outfile = ft_cnt_outfile(main->table);
	if (nbr_outfile == 0) // no outfile
		main->data->fd_out = STDOUT_FILENO;
	else
		main->data->fd_out = ft_getfd_out(main);
}