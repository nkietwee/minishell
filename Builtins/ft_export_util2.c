/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_util2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:10:53 by nkietwee          #+#    #+#             */
/*   Updated: 2023/10/10 15:49:04 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_find_repeat(char *find, t_dict *dict)
{
	while (dict)
	{
		if (ft_strcmp(dict->tmp_dict->key, find) == 0)
			return (EXIT_SUCCESS);
		dict = dict->next;
	}
	return (EXIT_FAILURE);
}

void	ft_instead_value(char **find, t_dict *dict)
{
	int	i;

	i = 0;
	while (dict)
	{
		if (ft_strcmp(dict->tmp_dict->key, find[0]) == 0)
		{
			free (dict->tmp_dict->value);
			if (find && find[1])
				dict->tmp_dict->value = ft_strdup(find[1]);
			else
				dict->tmp_dict->value = NULL;
		}
		dict = dict->next;
	}
}

void	ft_dbfree(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int	ft_cnt_repeat(char **str, t_dict *dict)
{
	int		i;
	int		repeat;
	char	**sp;

	i = 0;
	repeat = 0;
	while (str[i])
	{
		sp = ft_split(str[i], '=');
		if (ft_find_repeat(sp[0], dict) == EXIT_SUCCESS)
			repeat++;
		ft_dbfree(sp);
		i++;
	}
	return (repeat);
}

int	key_scan(t_dict_value value, t_dict *dict)
{
	char	*key;
	int		i;

	i = 0;
	while (dict)
	{
		key = dict->tmp_dict->key;
		if (ft_strcmp(key, value.key) == 0)
			return (i);
		i++;
		dict = dict->next;
	}
	return (-1);
}
