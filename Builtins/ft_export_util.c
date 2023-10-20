/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 17:03:35 by nkietwee          #+#    #+#             */
/*   Updated: 2023/10/10 14:11:24 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_dict	*pick_dict(t_dict *dict, int index)
{
	while (index > 0)
	{
		index--;
		dict = dict->next;
	}
	return (dict);
}

void	add_dict_node(t_dict *dict, t_dict *node, t_dict_value value)
{
	node->tmp_dict->key = value.key;
	if (value.value != NULL)
		node->tmp_dict->value = value.value;
	else
		node->tmp_dict->value = NULL;
	ft_lstadd_back_dict(&dict, node);
}

void	pick_value_n_slide(t_dict_value *value, char **str)
{
	size_t	i;

	i = 0;
	while ((*str)[i] != '=' && (*str)[i])
		i++;
	value->key = ft_substr((*str), 0, i);
	while (i > 0)
	{
		(*str)++;
		i--;
	}
	if (*(*str) == '=')
		(*str)++;
	else
	{
		value->value = NULL;
		return ;
	}
	while ((*str)[i])
		i++;
	value->value = ft_substr((*str), 0, i + 1);
}
