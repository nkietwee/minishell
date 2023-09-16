/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:32:57 by nkietwee          #+#    #+#             */
/*   Updated: 2023/08/27 17:20:33 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* update oldpwd pwd
getcwd
*/

void	ft_env(t_data *data)
{
	int	i;
	t_dict *new_dict;

	i = 0;
	// new_dict = ft_export(data->env_start);
	while (new_dict)
	{
		ft_putstr_fd(new_dict->tmp_dict->key, STDOUT_FILENO);
		ft_putstr_fd("=", STDOUT_FILENO);
		ft_putstr_fd(new_dict->tmp_dict->value, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		new_dict = new_dict -> next;
	}
	// printf("END\n");
	// printf("env\n");

}