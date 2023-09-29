/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 14:50:46 by ptungbun          #+#    #+#             */
/*   Updated: 2023/09/30 01:33:20 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int error_exit(t_minishell *ms, char *line)
{
	t_list *tk_lst;

	free(line);
	tk_lst = ms->tk_lst;
	printf("error\n");
	ft_lstclear(&tk_lst, &free);
	return (1);
}

static int special_char_validate(t_minishell *ms)
{
	t_list *tk_lst;
	t_token *token;

	tk_lst = ms->tk_lst;
	tk_lst = ft_lstlast(tk_lst);
	token = ((t_token *)(tk_lst->data));
	if (token->type == HEREDOC || token->type == INFILE ||
		token->type == APPEND || token->type == OUTFILE || token->type == PIPE)
		return (1);
	return (0);
}

int lexer(char *line, t_minishell *ms)
{
	// printf("c1\n");
	if (init_command_list(&ms, line))
		return (error_exit(ms, line));
	// printf("c2\n");
	if (quotes_validate(ms))
		return (error_exit(ms, line));
	// printf("c3\n");
	if (tokenize(&ms))
		return (error_exit(ms, line));
	// printf("c4\n");
	if (special_char_validate(ms))
		return (error_exit(ms, line));
	// printf("c5\n");
	free(line);
	// printf("c6\n");
	return (0);
}
