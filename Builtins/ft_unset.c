/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:33:14 by nkietwee          #+#    #+#             */
/*   Updated: 2023/09/28 15:53:44 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_dict	*ft_lstdelete_node(t_dict *dict, int index)
{
	t_dict *head;
	t_dict *start;

	head = dict;
	start = dict;
	if (index == 0)
	{
		dict = dict -> next;
		return (dict);
	}
	else
	{
		while (index + 1 != 1) // fixed index == 0
		{
			start = dict;
			dict = dict -> next;
			index--;
		}
		start->next = dict->next;
		dict = head;
		return(dict);
	}
	// return (dict); //??
	// ft_prtdict(dict);
}

int		ft_findkey_export(char *key, char **env)
{
	t_dict *dict_export;
	int	i;

	export = ft_export(NULL, env);
	i = 0;
	while (dict_export->tmp_dict)
	{
		if (ft_strcmp(dict->tmp_dict->key, key) == EXIT_SUCCESS)
			return (i);
		i++;
		dict_export->tmp_dict = dict_export->tmp_dict->next;
	}
	return (-1);
}

void	ft_unset(char **cmd, t_dict *tmp_export)
{
	int	i;
	int	index;

	i = 1;
	while (cmd[i])
	{
		// index = ft_findkey_export(cmd[0], env);
		if (index == -1)
			continue;
		ft_lstdelete_node(tmp_export, index);
		i++;
	}
}