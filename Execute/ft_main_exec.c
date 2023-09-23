/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 17:14:59 by nkietwee          #+#    #+#             */
/*   Updated: 2023/09/23 23:59:04 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
// void	ft_changetype()
// {

// }


// void	ft_init_buildin(t_list *tb_lst)
// {
// 	t_table *table;
// 	// t_rdr	*rdr_lst;

// 	while (tb_lst)
// 	{
// 		table = (t_table *)(tb_lst->data);
// 		// rdr_lst = (table->cmd)
// 		if (table->cmd)

// 			// ft_findstr(table);
// 			// printf("found cmd\n");
// 		tb_lst = tb_lst->next;
// 	}
// }

void	ft_mainexec(t_minishell *ms)
{
	// printf("main_exec\n");
	if (ft_checkfile(ms->tb_lst) == EXIT_FAILURE)
		return ;
	// ft_init_buildin(ms->tb_lst);
	// exit (0);
	ft_countexec(ms);
	// ft_heredoc(ms->tb_lst , ms->data.nbr_heredoc);
	// printf("before execute\n");
	ft_execute(ms->tb_lst);
}