/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 15:48:06 by nkietwee          #+#    #+#             */
/*   Updated: 2023/10/10 23:26:05 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_addvalueexport(char **av, t_dict *dict)
{
	int				i;
	int				index;
	t_dict_value	value;
	t_dict			*node;
	char			*str;

	i = 1;
	while (av[i])
	{
		str = av[i];
		pick_value_n_slide(&value, &str);
		index = key_scan(value, dict);
		if (index == -1)
			add_dict_node(dict, ft_lstnew_dict(malloc(sizeof(t_dict))), value);
		else
		{
			if (value.value)
			{
				node = pick_dict(dict, index);
				free(node->tmp_dict->value);
				node->tmp_dict->value = value.value;
			}
		}
		i++;
	}
}

void	ft_swap(t_dict **dict)
{
	char	*tmp_key;
	char	*tmp_value;

	tmp_key = NULL;
	tmp_value = NULL;
	tmp_key = (*dict)->next->tmp_dict->key;
	tmp_value = (*dict)->next->tmp_dict->value;
	(*dict)->next->tmp_dict->key = (*dict)->tmp_dict->key;
	(*dict)->next->tmp_dict->value = (*dict)->tmp_dict->value;
	(*dict)->tmp_dict->key = tmp_key;
	(*dict)->tmp_dict->value = tmp_value;
}

void	ft_lstascend(t_dict *dict)
{
	t_dict	*head;
	t_dict	*head2;
	int		i;
	int		size;

	i = 0;
	size = ft_lstsize_dict(dict);
	head2 = dict;
	head = dict;
	while (i < size - 1)
	{
		dict = head;
		while (dict && (dict)->next != NULL)
		{
			if (ft_strcmp((dict)->tmp_dict->key, \
			(dict)->next->tmp_dict->key) > 0)
				ft_swap(&dict);
			else
				(dict) = (dict)->next ;
		}
		i++;
	}
	ft_prtexport(head2);
}

/* check first character of variable(key) */
void	ft_checkname(char **cmd)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		if (ft_isalpha(cmd[i][0]) == EXIT_FAILURE)
		{
			ft_putstr_fd("bash: export: `", STDERR_FILENO);
			ft_putstr_fd(cmd[i], STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDOUT_FILENO);
		}
		i++;
	}
}

void	ft_export(char **cmd, t_dict **dict)
{
	int	len;

	ft_checkname(cmd);
	len = ft_cntstr(cmd);
	if (len == 1)
		ft_lstascend(*dict);
	if (len > 1)
		ft_addvalueexport(cmd, *dict);
}
