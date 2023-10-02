/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:32:57 by nkietwee          #+#    #+#             */
/*   Updated: 2023/10/02 21:00:15 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* update oldpwd pwd
getcwd
*/

// void	ft_env(t_data *data)
// void	ft_env(char **env)
void	ft_env(t_dict *new_dict)
{
	int	i;
	// t_dict *new_dict;

	i = 0;
	// dprintf(2, "env\n");
	// new_dict = ft_export(data->env_start);
	// ft_putstr_fd(new_dict->tmp_dict->key, STDOUT_FILENO);
	// exit(0);
	while (new_dict)
	{
		ft_putstr_fd(new_dict->tmp_dict->key, STDOUT_FILENO);
		if (new_dict->tmp_dict->value)
			ft_putstr_fd("=", STDOUT_FILENO);
		ft_putstr_fd(new_dict->tmp_dict->value, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		new_dict = new_dict -> next;
	}
	// while(env[i])
	// {
	// 	ft_putstr_fd(env[i], STDOUT_FILENO);
	// 	// ft_putstr_fd("=", STDOUT_FILENO);
	// 	// ft_putstr_fd(new_dict->tmp_dict->value, STDOUT_FILENO);
	// 	ft_putstr_fd("\n", STDOUT_FILENO);
	// 	i++;
	// }
	// printf("END\n");
	// printf("env\n");

}