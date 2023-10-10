/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getfile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 18:46:22 by nkietwee          #+#    #+#             */
/*   Updated: 2023/10/11 00:26:48 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_accessfile(char *file, int type)
{
	if (type == HEREDOC || type == OUTFILE || type == APPEND)
		return (EXIT_SUCCESS);
	if (access(file, F_OK) == 0)
	{
		if (access(file, R_OK | F_OK) == -1)
		{
			ft_prterrexec(file, PER_FILE);
			return (EXIT_FAILURE);
		}
	}
	else
	{
		ft_prterrexec(file, NO_FILE);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_access_outfile(char *file, int type)
{
	if (type == HEREDOC || type == INFILE)
		return (EXIT_SUCCESS);
	if (access(file, F_OK) == 0)
	{
		if (access(file, R_OK | F_OK) == -1)
		{
			ft_prterrexec(file, PER_FILE);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int	ft_getfd_in(t_list *tb_lst)
{
	int		fd_in;
	int		i;
	t_table	*table;
	t_rdr	*rdr;
	t_list	*rdr_lst;

	i = 0;
	table = (t_table *)(tb_lst->data);
	rdr_lst = (t_list *)(table->rdr);
	while (rdr_lst)
	{
		rdr = (t_rdr *)(rdr_lst->data);
		if (ft_accessfile(rdr->file, rdr->type) == EXIT_FAILURE)
			return (-1);
		if (rdr->type == INFILE)
			fd_in = open(rdr->file, O_RDONLY);
		else if (rdr->type == HEREDOC)
			fd_in = table->exec_data.fd_heredoc;
		rdr_lst = rdr_lst->next;
	}
	return (fd_in);
}

int	ft_getfd_out(t_list *tb_lst)
{
	int		fd_out;
	t_table	*table;
	t_rdr	*rdr_lst;

	while (tb_lst)
	{
		table = (t_table *)(tb_lst->data);
		while (table->rdr)
		{
			rdr_lst = (t_rdr *)(table->rdr->data);
			if (ft_access_outfile(rdr_lst->file, rdr_lst->type) == 1)
				return (-1);
			if (rdr_lst->type == OUTFILE)
			{
				fd_out = open(rdr_lst->file, O_RDWR | O_CREAT | O_TRUNC, 0644);
			}
			else if (rdr_lst->type == APPEND)
				fd_out = open(rdr_lst->file, O_RDWR | O_CREAT | O_APPEND, 0644);
			table->rdr = table->rdr->next;
		}
		tb_lst = tb_lst->next;
	}
	return (fd_out);
}

void	ft_getfd(t_list *tb_lst)
{
	t_table	*table;
	t_data	*exec_data;

	table = (t_table *)(tb_lst->data);
	exec_data = &table->exec_data;
	exec_data->nbr_infile = ft_cnt_infile(tb_lst);
	if (exec_data->nbr_infile == 0 && exec_data->nbr_heredoc == 0)
		exec_data->fd_in = STDIN_FILENO;
	else
		exec_data->fd_in = ft_getfd_in(tb_lst);
	exec_data->nbr_out_append = ft_cnt_outfile(tb_lst);
	if (exec_data->nbr_out_append == 0)
		exec_data->fd_out = STDOUT_FILENO;
	else
		exec_data->fd_out = ft_getfd_out(tb_lst);
}
