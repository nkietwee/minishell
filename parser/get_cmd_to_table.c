/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_to_table.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 16:05:36 by ptungbun          #+#    #+#             */
/*   Updated: 2023/09/17 15:01:17 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static size_t	count_cmd_n_arg(t_list *lst)
{
	size_t	size;
	t_token *token;

	size = 0;
	token = lst->data;
	while(lst && token->type != PIPE)
	{
		size++;
		lst = lst->next;
		if (lst)
			token = lst->data;
	}
	return (size);
}

static char	**get_cmd_n_slide(t_list **lst)
{
	t_token *token;
	char	**str_ar;
	size_t	size;

	token = (*lst)->data;
	size = count_cmd_n_arg(*lst);
	str_ar = ft_calloc(sizeof(char *), size + 1);
	size = 0;
	while (*lst && token->type != PIPE)
	{
		if (token->type == CMD || token->type == ARG)
		{
			str_ar[size] = ft_strdup(token->str);
			size++;
		}
		*lst = (*lst)->next;
		if (*lst)
			token = (*lst)->data;
	}
	return (str_ar);
}

int	get_cmd_to_table(t_minishell **ms)
{
	t_table	*table;
	t_list	*lst;

	(*ms)->tb_lst = NULL;
	lst = (*ms)->tk_lst;
	while (lst)
	{
		if ((*ms)->tb_lst == NULL)
			(*ms)->tb_lst = ft_lstnew(malloc(sizeof(t_table)));
		else
			ft_lstadd_back(&((*ms)->tb_lst), ft_lstnew(malloc(sizeof(t_table))));
		table = (ft_lstlast((*ms)->tb_lst))->data;
		table->cmd = get_cmd_n_slide(&lst);
		table->rdr = NULL;
		if (lst && ((t_token *)((lst->data)))->type == PIPE)
			lst = lst->next;
	}
	return (0);
}
