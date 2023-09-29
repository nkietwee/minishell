/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paser.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 14:52:19 by ptungbun          #+#    #+#             */
/*   Updated: 2023/09/29 23:11:56 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int error_exit(t_minishell *ms)
{
	t_list *tk_lst;

	tk_lst = ms->tk_lst;
	printf("error\n");
	ft_lstclear(&tk_lst, &free);
	return (1);
}

int paser(t_minishell *ms)
{
	// if (expand_var(&ms))
	// 	return (error_exit(ms));
	if (get_cmd_to_table(&ms))
		return (error_exit(ms));
	if (get_rdr_to_table(&ms))
		return (error_exit(ms));
	// if (validate_table(ms))
	// 	return (error_exit(ms));
	return (0);
}
