/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_n_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 16:15:57 by ptungbun          #+#    #+#             */
/*   Updated: 2023/09/29 22:56:33 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	expand_in_quotes(char **ep_str, t_dict *dict)
{
	char	*s[3];
	char	*str;
	size_t	posi[2];
	size_t	i;

	i = 0;
	while((*ep_str)[i] && (*ep_str)[i] != '$')
		i++;
	posi[0] = i;
	while((*ep_str)[i] && !ft_isalpha((*ep_str)[i]))
		i++;
	posi[1] = i;
	s[0] = ft_substr(*ep_str, 0, posi[0] + 1);
	s[1] = ft_substr(*ep_str, posi[0], posi[1] - posi[0] + 1);
	s[2] = ft_substr(*ep_str, posi[1], ft_strlen(*ep_str) - posi[1]);
	while(dict)
	{
		if (ft_strncmp(s[1], dict->tmp_dict->key, ft_strlen(s[1])) && \
		ft_strncmp(dict->tmp_dict->key, s[1], ft_strlen(dict->tmp_dict->key)))
		{
			free(*ep_str);
			str = ft_strcat_n_free(s[0], s[1]);
			*ep_str = ft_strcat_n_free(str, s[2]);
			return ;
		}
		dict = dict->next;
	}
}

static void	expand(char **ep_str, t_dict *dict)
{
	while(dict)
	{
		if (ft_strncmp(*ep_str, dict->tmp_dict->key, ft_strlen(*ep_str)) && \
		ft_strncmp(dict->tmp_dict->key, *ep_str, ft_strlen(dict->tmp_dict->key)))
		{
			free(*ep_str);
			*ep_str = ft_strdup(dict->tmp_dict->value);
			return ;
		}
		dict = dict->next;
	}
}

void	scan_n_expand(t_list **ep_lst, t_dict *dict)
{
	char	*ep_str;
	t_list	*ep_lst_ptr;

	ep_lst_ptr = *ep_lst;
	while(ep_lst_ptr)
	{
		ep_str = (char *)((ep_lst_ptr)->data);
		if (*ep_str == '\"')
			expand_in_quotes(&ep_str, dict);
		else if (*ep_str == '$')
			expand(&ep_str, dict);
		ep_lst_ptr = ep_lst_ptr->next;
	}
}
