/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 17:14:59 by nkietwee          #+#    #+#             */
/*   Updated: 2023/10/02 01:25:28 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
// echo
// cd
// pwd
export
unset
// env
exit
*/

void	ft_buildin_onecmd(t_minishell *ms)
{
	t_table	*table;
	t_dict	*tmp_env;


	// tmp_env =  ft_getenv(ms->env);

	table = (t_table *)(ms->tb_lst->data);
	ft_getfd(ms->tb_lst);
	// dprintf(2, "buildin_onecmd\n");
	if (ms->nbr_cmd)
	{
		if (ft_strcmp(table->cmd[0], "echo") == 0)
			ft_echo(table->cmd , table->exec_data.fd_out);
		if (ft_strcmp(table->cmd[0], "cd") == 0)
			ft_cd(table->cmd);
		if (ft_strcmp(table->cmd[0], "pwd") == 0)
			ft_pwd();
		if (ft_strcmp(table->cmd[0], "export") == 0)
			ft_export(table->cmd, ms->dict);
		if (ft_strcmp(table->cmd[0], "env") == 0)
			ft_env(ms->dict);
		if (ft_strcmp(table->cmd[0], "unset") == 0)
			ft_unset(table->cmd, &ms->dict);
		// if (ft_strcmp(table->cmd[0], "exit") == 0)
		// 	ft_exit();
		// exit(0);
	}
}
void	ft_mainexec(t_minishell *ms)
{
	// if (ft_checkfile(ms->tb_lst) == EXIT_FAILURE)
	// 	return ;
	// ft_countexec(ms);
	// ft_heredoc(ms->tb_lst , ms->nbr_heredoc);
	// ft_heredoc(ms->tb_lst , 3);

	ms->nbr_cmd = ft_cntcmd(ms->tb_lst);
	ft_initdata_exec(ms->tb_lst);
	// dprintf(2, "main_exec\n");
	ft_buildin_onecmd(ms);
	// printf("nbr_cmd : %d\n" , ms->nbr_cmd);
	ft_execute(ms->tb_lst, ms->env, ms->nbr_cmd);

}