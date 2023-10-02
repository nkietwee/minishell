/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prtlinklist.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 17:25:43 by nkietwee          #+#    #+#             */
/*   Updated: 2023/10/02 20:48:28 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_prtdict_value(t_dict_value	**tmp_value)
{
	int	i;
	// int	len;

	i = 0;
	// // len = ft_cntdict_export(tmp_value);
	// dprintf(2, "len : %d\n", len);
	while (tmp_value[i])
	{
		printf("tmp_main : %s\n", tmp_value[i]->key);
		printf("tmp_main : %s\n\n", tmp_value[i]->value);
		i++;
	}
}

void	ft_prtdict(t_dict	*dict)
{
	int	i;

	i = 0;
	while (dict)
	{
		// printf("tmp_main : %s\n", dict->tmp_dict->key);
		// printf("tmp_main : %s\n\n", dict->tmp_dict->value);
		printf("%s=%s\n", dict->tmp_dict->key ,dict->tmp_dict->value);
		dict = dict -> next;
		i++;
	}
	dprintf(2, "i : %d\n", i);
}

void	ft_prtexport(t_dict	*dict)
{
	int	i;

	i = 0;
	while (dict)
	{
		// printf("tmp_main : %s\n", dict->tmp_dict->key);
		// printf("tmp_main : %s\n\n", dict->tmp_dict->value);
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(dict->tmp_dict->key, STDOUT_FILENO);
		ft_putstr_fd("=", STDOUT_FILENO);
		ft_putstr_fd(dict->tmp_dict->value, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		// printf("%s=%s\n", dict->tmp_dict->key ,dict->tmp_dict->value);
		dict = dict -> next;
	}
}