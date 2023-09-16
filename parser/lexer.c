/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 14:50:46 by ptungbun          #+#    #+#             */
/*   Updated: 2023/09/17 02:30:57 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	error_exit(t_minishell *ms, char *line)
{
	t_list	*lst;

	(void)line;
	lst = ms->lst;
	printf("error\n");
	ft_lstclear(&lst, &free);
	return (1);
}

static int special_char_validate(t_minishell *ms)
{
	t_list	*lst;
	t_token	*token;

	lst = ms->lst;
	lst = ft_lstlast(lst);
	token = ((t_token *)(lst->data));
	if(token->type == HEREDOC || token->type == INFILE || \
	token->type == APPEND || token->type == OUTFILE || token->type == PIPE)
		return (1);
	return (0);
}

int	lexer(char *line, t_minishell *ms)
{
	if (init_command_list(&ms, line))
		return (error_exit(ms, line));
	if (!ms->lst)
		return (1);
	if (quotes_validate(ms))
		return (error_exit(ms, line));
	if (tokenize(&ms))
		return (error_exit(ms, line));
	if (special_char_validate(ms))
		return (error_exit(ms, line));
	// printf("type = %d\n", ((t_token *)ms->lst->data)->type);
	// ms->lst = ms->lst->next;
	// printf("type = %d\n", ((t_token *)ms->lst->data)->type);
	// ms->lst = ms->lst->next;
	// printf("type = %d\n", ((t_token *)ms->lst->data)->type);
	return (0);
}


