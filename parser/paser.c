/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paser.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 14:52:19 by ptungbun          #+#    #+#             */
/*   Updated: 2023/09/17 02:31:03 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	error_exit(t_minishell *ms)
{
	t_list	*lst;

	lst = ms->lst;
	printf("error\n");
	ft_lstclear(&lst, &free);
	return (1);
}

int	paser(t_minishell *ms)
{
	// if (expand_var(&ms))
	// 	return (error_exit(ms));
	if (get_cmd_to_table(&ms))
		return (error_exit(ms));
	if (get_rdr_to_table(&ms))
		return (error_exit(ms));
	// if (token_clear(&ms))
	// 	return (error_exit(ms));
	return (1);
}
