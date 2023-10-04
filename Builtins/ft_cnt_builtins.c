/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cnt_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamwayk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 12:54:40 by nkietwee          #+#    #+#             */
/*   Updated: 2023/10/04 12:36:42 by pnamwayk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cntdict(t_dict **dict)
{
	int	i;

	i = 0;
	while (dict[i])
		i++;
	return (i);
}

int	ft_cntdictmain(t_dict *dict)
{
	int	i;

	i = 0;
	while (dict)
	{
		i++;
		dict = dict->next;
	}
	return (i);
}

int	ft_cntdict_export(t_dict_value **dict)
{
	int	i;

	i = 0;
	while (dict[i])
		i++;
	return (i);
}

int	ft_cntstr(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
