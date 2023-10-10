/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 18:26:45 by nkietwee          #+#    #+#             */
/*   Updated: 2023/10/11 00:04:56 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_execute(t_minishell *ms, t_list *tb_lst)
{
	int		fd_read;
	t_table	*table;
	int		i;

	fd_read = 0;
	i = 0;
	ms->pid = malloc(sizeof(pid_t) * ft_lstsize(ms->tb_lst));
	while (tb_lst)
	{
		table = (t_table *)(tb_lst->data);
		ft_openpipe(ms, table, i);
		if (table->cmd[0])
			table->exec_status = ft_check_builtin(table->cmd);
		ms->pid[i] = fork();
		if (ms->pid[i] == -1)
			ft_prterr(CANNT_FORK, "Fork");
		if (ms->pid[i] == 0)
			branch_child(ms, tb_lst, &fd_read);
		if (ms->pid[i] > 0)
			branch_parent(ms, tb_lst, &fd_read);
		tb_lst = tb_lst->next;
		i++;
	}
	ft_waitpid(ms);
}
