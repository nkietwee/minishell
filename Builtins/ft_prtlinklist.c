/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prtlinklist.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 17:25:43 by nkietwee          #+#    #+#             */
/*   Updated: 2023/08/27 17:26:00 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_prtdict_value(t_dict_value	**tmp_value)
{
	int	i;
	int	len;

	i = 0;
	len = ft_cntdict_export(tmp_value);
	while (i < len)
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
	}
}