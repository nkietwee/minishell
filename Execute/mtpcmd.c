/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtpcmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 00:31:45 by nkietwee          #+#    #+#             */
/*   Updated: 2023/09/17 02:38:28 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
void	ft_findpath(t_data *data)
{
	int		i;
	// char	**path;

	i = 0;
	while (1)
	{
		if (data->tmp_env[i][0] == 'P' && data->tmp_env[i][1] == 'A' \
		&& data->tmp_env[i][2] == 'T' && data->tmp_env[i][3] == 'H')
			break;
		i++;
	}
	data->path = ft_split(data->tmp_env[i] + 5, ':');
	i = 0;
	while (data->path[i])
	{
		data->path[i] = ft_strjoinextra(data->path[i], "/" , BEFORE);
		i++;
	}
}

void	ft_initvalue(t_data *data, char **env, char **av, int ac)
{
	data->tmp_env = env;
	data->tmp_ac = ac;
	data->tmp_av = av;


}

// void	ft_addcmd(int ac, char **av, t_data *data)
// {
// 	int	i;

// 	i = 2;
// 	while (i < ac)
// 	{


// 	}
// }

// int	main(int ac, char **av, char **env)
// {
// 	(void)ac;
// 	(void)av;
// 	t_minishell main;

// 	ft_initvalue(main.data, env, av, ac);
// 	// ft_findpath(&data);
// 	printf("mainexec\n");
// 	exit(0);
// 	ft_mainexec(&main, ac, av);

// }
