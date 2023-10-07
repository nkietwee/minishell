/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamwayk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 17:14:59 by nkietwee          #+#    #+#             */
/*   Updated: 2023/10/07 16:15:44 by pnamwayk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	ft_builtin_onecmd(t_minishell *ms)
// {
// 	t_table	*table;
// 	// t_dict	*tmp_env;

// 	table = (t_table *)(ms->tb_lst->data);
// 	if (ft_check_builtin(table->cmd) == EXIT_SUCCESS)
// 		ft_getfd(ms, tb_lst);
// 	if (ms->nbr_cmd)
// 	{
// 		if (ft_strcmp(table->cmd[0], "echo") == 0)
// 			ft_echo(table->cmd , table->fd_out);
// 		if (ft_strcmp(table->cmd[0], "cd") == 0)
// 			ft_cd(table->cmd, ms->dict);
// 		if (ft_strcmp(table->cmd[0], "pwd") == 0)
// 			ft_pwd();
// 		if (ft_strcmp(table->cmd[0], "export") == 0)
// 			ft_export(table->cmd, ms->dict);
// 		if (ft_strcmp(table->cmd[0], "env") == 0)
// 			ft_env(ms->dict);
// 		if (ft_strcmp(table->cmd[0], "unset") == 0)
// 			ft_unset(table->cmd, &ms->dict);
// 		if (ft_strcmp(table->cmd[0], "exit") == 0)
// 			ft_exit(table->cmd, ms->dict);
// 	}
// }

void	ft_mainexec(t_minishell *ms)
{
	// if (ft_checkfile(ms->tb_lst) == EXIT_FAILURE)
	// 	return ;
	// ft_countexec(ms);
	// t_table	*table;

	// int i = 0;
	// while(ms->tb_lst)
	// {

		// table = (t_table *)(ms->tb_lst->data);
		// if (table->cmd[0] != NULL)
		// {
		// 	if(table->cmd[0])
		// 		dprintf(2, "%d cmd[0] : %s\n" , i, table->cmd[0]);
		// 	if(table->cmd[1])
		// 		dprintf(2, "%d cmd[1] : %s\n" , i, table->cmd[1]);
		// 	if(table->cmd[2])
		// 		dprintf(2, "%d cmd[2] : %s\n" , i, table->cmd[2]);
		// 	dprintf(2, "%d i : %d\n" , i, table->i);
		// 	dprintf(2, "%d fd_heredoc : %d\n" , i, table->fd_heredoc);
		// 	dprintf(2, "%d nbr_heredoc : %d\n" , i, table->nbr_heredoc);
		// 	// dprintf(2, "fd_in : %d\n" , table->exec_data->fd_in);
		// 	i++;
		// }
		// 	ms->tb_lst = ms->tb_lst->next;
		// }

	// table = (ms->tb_lst->data);
	ms->all_heredoc = ft_cnt_heredoc(ms->tb_lst);

	dprintf(2, "all_here : %d\n" , ms->all_heredoc);
	if (ms->all_heredoc > 0)
		ft_heredoc(ms->tb_lst);
	// dprintf(2, "fd_here : %d\n", table->fd_heredoc);
	// ft_heredoc(ms->tb_lst , 3);
	// exit(0);
	ms->nbr_cmd = ft_cntcmd(ms->tb_lst);
	dprintf(2, "nbr_cmd : %d\n" , ms->nbr_cmd);

	if (ms->nbr_cmd == 0)
		return;
	// ft_initdata_exec(ms->tb_lst);
	// ft_initdata_exec(ms->tb_lst);
	ft_initdata_exec(ms->tb_lst , ms->env);
	// dprintf(2, "env : %s\n", table->tmp_env[0] );

	// ft_builtin_onecmd(ms);
	// dprintf(2, "nbr_cmd : %d\n" , ms->nbr_cmd);
	ft_execute(ms, ms->tb_lst);

	// ft_execute(ms->tb_lst, ms->dict, ms->nbr_cmd);

}
