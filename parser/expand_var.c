/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 22:50:36 by nkietwee          #+#    #+#             */
/*   Updated: 2023/09/29 22:56:03 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static size_t	expand_logic(char *tk_str)
{
	size_t	i;
	char	quote;

	quote = '\0';
	i = 1;
	if (*tk_str == '$')
	{
		while (tk_str[i] && (tk_str[i] == '\'' || tk_str[i] == '\"'))
			i++;
	}
	else if (*tk_str == '\'' || *tk_str == '\"')
	{
		quote = *tk_str;
		while (tk_str[i] && tk_str[i] != quote)
			i++;
	}
	else
	{
		i = 0;
		while (tk_str[i] && (tk_str[i] == '\'' || tk_str[i] == '\"' || \
		tk_str[i] == '$'))
			i++;
	}
	if (tk_str[i])
		i++;
	return (i);
}

static t_list	*init_expand_lst(char *tk_str)
{
	size_t	size;
	t_list	*ep_lst;

	ep_lst = NULL;
	while(*tk_str)
	{
		size = expand_logic(tk_str);
		if(!ep_lst)
			ep_lst = ft_lstnew(ft_substr(tk_str, 0, size));
		else
			ft_lstadd_back(&ep_lst, ft_lstnew(ft_substr(tk_str, 0, size)));
		while(size > 0)
		{
			(tk_str)++;
			size--;
		}
	}
	return (ep_lst);
}

static void	ep_lst_to_str(char **str, t_list **ep_lst)
{
	char	*new_str;

	new_str = "\0";
	while((*ep_lst))
	{
		new_str = ft_strcat_n_free(*str, (char *)((*ep_lst)->data));
		(*ep_lst) = (*ep_lst)->next;
	}
	free(*str);
	*str = new_str;
}

void	quotes_remove(t_list **ep_lst)
{
	char	*ep_str;

	while((*ep_lst))
	{
		ep_str = (*ep_lst)->data;
		if (*ep_str == '\'' || *ep_str == '\"')
		{
			free(ep_str);
			((*ep_lst)->data) = ft_substr(ep_str, 1, ft_strlen(ep_str) - 2);
		}
		(*ep_lst) = (*ep_lst)->next;
	}
}

int	expand_var(t_minishell **ms)
{
	t_list	*tk_lst;
	t_token	*token;
	t_dict	*dict;
	t_list	*ep_lst;

	tk_lst = (*ms)->tk_lst;
	dict = (*ms)->dict;
	while (tk_lst)
	{
		token = tk_lst->data;
		ep_lst = init_expand_lst(token->str);
		scan_n_expand(&ep_lst, dict);
		quotes_remove(&ep_lst);
		ep_lst_to_str(&token->str, &ep_lst);
		ft_lstclear(&ep_lst, &free);
		tk_lst = tk_lst->next;
	}
	return (0);
}
