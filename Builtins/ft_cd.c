/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:32:39 by nkietwee          #+#    #+#             */
/*   Updated: 2023/10/01 17:20:45 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*update env*/

void	ft_cd(char **cmd)
{
	char	pre_path[128];
	char	*tmp;
	char	*old_pwd;
	int		errno;

	errno = 0;
	old_pwd = getcwd(NULL, 0);
	// dprintf(2, "ft_cd\n");
	// dprintf(2, "path : %s\n" , cmd[1]);
	// chdir(cmd[1]);
	// printf("fn_cd\n");
	// printf("cmd[1] : %s\n" ,cmd[1]);
	// if (str)
	// 	ft_getnewenv(NULL, data->env_start);

	// if (cmd[1] == NULL || ft_findcmd(cmd[1], "~", 1) == EXIT_SUCCESS)
	if (cmd[1] == NULL || ft_findstr(cmd[1], "~", 1) == EXIT_SUCCESS)
		cmd[1] = getenv("HOME");
	// if (ft_cmd[1]cmp(cmd[1], "-") == EXIT_SUCCESS) // left test
	// {
	//     tmp = getcwd(pre_path, 128);
	//     if (!tmp)
	//         return ;
	//     chdir(pre_path);
	// }
	if (access(cmd[1], F_OK) == 0)
	{
		if (access(cmd[1], R_OK | F_OK) == 0)
			chdir(cmd[1]);
		else
			ft_prterr_builtins(CANNT_OPEN, "cd", cmd[1], errno);
			// dprintf(2, "Err\n");
	}
	else
		ft_prterr_builtins(PER_DN, "cd",cmd[1], errno);
		// dprintf(2, "Err\n");

}