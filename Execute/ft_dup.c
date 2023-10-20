/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 00:04:30 by nkietwee          #+#    #+#             */
/*   Updated: 2023/10/11 00:06:49 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_dup2_end(t_list *tb_lst, int *fd_tmp_read)
{
	t_table	*table;
	t_data	*exec_data;

	table = (t_table *)(tb_lst->data);
	exec_data = (t_data *)(&(table->exec_data));
	if (exec_data->nbr_infile || exec_data->nbr_heredoc)
		dup2(exec_data->fd_in, STDIN_FILENO);
	else
		dup2(*fd_tmp_read, STDIN_FILENO);
	dup2(exec_data->fd_out, STDOUT_FILENO);
}

void	ft_dup2_1cmd(t_list *tb_lst)
{
	t_table	*table;
	t_data	*exec_data;

	table = (t_table *)(tb_lst->data);
	exec_data = (t_data *)(&(table->exec_data));
	dup2(exec_data->fd_in, STDIN_FILENO);
	dup2(exec_data->fd_out, STDOUT_FILENO);
	if (exec_data->fd_in != STDIN_FILENO)
		close(exec_data->fd_in);
	if (exec_data->fd_out != STDOUT_FILENO)
		close(exec_data->fd_out);
}

void	ft_dup2_start(t_list *tb_lst)
{
	t_table	*table;
	t_data	*exec_data;

	table = (t_table *)(tb_lst->data);
	exec_data = (t_data *)(&(table->exec_data));
	dup2(exec_data->fd_in, STDIN_FILENO);
	if (exec_data->nbr_out_append)
		dup2(exec_data->fd_out, STDOUT_FILENO);
	else
		dup2(table->fd_pipe[1], STDOUT_FILENO);
}

void	ft_dupbtw(t_list *tb_lst, int *fd_tmp_read)
{
	t_table	*table;
	t_data	*exec_data;

	table = (t_table *)(tb_lst->data);
	exec_data = (t_data *)(&(table->exec_data));
	if (exec_data->nbr_infile || exec_data->nbr_heredoc)
		dup2(exec_data->fd_in, STDIN_FILENO);
	else
		dup2(*fd_tmp_read, STDIN_FILENO);
	if (exec_data->nbr_out_append)
		dup2(exec_data->fd_out, STDOUT_FILENO);
	else
		dup2(table->fd_pipe[1], STDOUT_FILENO);
}

void	ft_dup2(t_list *tb_lst, int *fd_tmp_read, int nbr_cmd)
{
	t_table	*table;
	t_data	*exec_data;

	table = (t_table *)(tb_lst->data);
	exec_data = (t_data *)(&(table->exec_data));
	if (exec_data->i == 0 && nbr_cmd == 1)
		ft_dup2_1cmd(tb_lst);
	else if (exec_data->i == 0 && nbr_cmd > 1)
		ft_dup2_start(tb_lst);
	else if (exec_data->i == nbr_cmd - 1)
		ft_dup2_end(tb_lst, fd_tmp_read);
	else
		ft_dupbtw(tb_lst, fd_tmp_read);
	if (exec_data->nbr_heredoc)
		ft_unlink(tb_lst);
}
