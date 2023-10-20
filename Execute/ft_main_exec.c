/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 17:14:59 by nkietwee          #+#    #+#             */
/*   Updated: 2023/10/11 00:19:40 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_waitpid(t_minishell *ms)
{
	int		i;
	t_list	*tb_lst;

	i = 0;
	tb_lst = ms->tb_lst;
	while (i < ft_lstsize(ms->tb_lst))
	{
		waitpid(ms->pid[i], &ms->status, 0);
		ms->exit_code = WEXITSTATUS(ms->status);
		tb_lst = tb_lst->next;
		i++;
	}
}

int	ft_check_builtin(char **cmd)
{
	if (cmd[0] == NULL)
		return (-1);
	if (ft_strcmp(cmd[0], "echo") == 0)
		return (BUI_CHILD);
	else if (ft_strcmp(cmd[0], "env") == 0)
		return (BUI_CHILD);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		return (BUI_CHILD);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		return (BUI_PARENT);
	else if (ft_strcmp(cmd[0], "cd") == 0)
		return (BUI_PARENT);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		return (BUI_PARENT);
	else if (ft_strcmp(cmd[0], "export") == 0)
	{
		if (cmd[1] == NULL)
			return (BUI_CHILD);
		return (BUI_PARENT);
	}
	return (CMD_);
}

void	ft_mainexec(t_minishell *ms)
{
	t_table	*table;

	table = (ms->tb_lst->data);
	table->nbr_heredoc = ft_cnt_heredoc(ms->tb_lst);
	ms->nbr_cmd_all = ft_cntcmd(ms->tb_lst);
	if (table->nbr_heredoc > 0)
		ft_main_heredoc(ms->tb_lst);
	if (ms->nbr_cmd_all == 0 && table->nbr_heredoc > 0)
		return ;
	ft_initdata_exec(ms->tb_lst);
	ft_execute(ms, ms->tb_lst);
}

void	ft_initdata_exec(t_list *tb_lst)
{
	t_table	*table;
	int		i_cnt;

	i_cnt = 0;
	table = (t_table *)(tb_lst->data);
	while (tb_lst)
	{
		table = (t_table *)(tb_lst->data);
		table->exec_data.i = i_cnt;
		table->exec_status = 0;
		table->exec_data.pid = 0;
		table->exec_data.fd_in = 0;
		table->exec_data.fd_out = 0;
		table->exec_data.nbr_infile = ft_cnt_infile(tb_lst);
		table->exec_data.nbr_out_append = 0;
		table->exec_data.nbr_heredoc = ft_cnt_heredoc(tb_lst);
		i_cnt++;
		tb_lst = tb_lst->next;
	}
}

void	ft_openpipe(t_minishell *ms, t_table *table, int i)
{
	if (ms->nbr_cmd_all > 1 && i != ms->nbr_cmd_all - 1)
	{
		if (pipe(table->fd_pipe) == -1)
			ft_prterr(CANNT_PIPE, "Pipe");
	}
}
