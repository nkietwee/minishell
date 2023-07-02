/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 21:51:39 by nkietwee          #+#    #+#             */
/*   Updated: 2023/06/27 16:07:27 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Include/minishell.h"

void    ft_cd(char *str)
{
	char pre_path[128];
	char    *tmp;
	
	if (ft_strcmp(str, "..") == EXIT_SUCCESS)
		chdir("..");
	if (ft_strcmp(str, ".") == EXIT_SUCCESS)
		chdir(".");
	// if (ft_strcmp(str, "-") == EXIT_SUCCESS) // left test
	// {
	//     tmp = getcwd(pre_path, 128);
	//     if (!tmp)
	//         return ;    
	//     chdir(pre_path);
	// }
	if (access(str, F_OK) == 0)
	{
		if (access(str, R_OK | F_OK) == 0)
			chdir(str);
		else
			ft_prterr(CANNT_OPEN, "cd", str, errno);
	}
	else
		ft_prterr(PER_DN, "cd",str, errno);
	
}