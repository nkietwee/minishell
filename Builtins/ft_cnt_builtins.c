/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cnt_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 12:54:40 by nkietwee          #+#    #+#             */
/*   Updated: 2023/10/02 01:18:37 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_cnt_at_equal(char *str)
{
	// return (ft_strlen(str) - ft_cnt_bf_equal(str) + 1);
	return (ft_strlen(str) - ft_cnt_bf_equal(str));
}

int	ft_cnt_bf_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ':')
			break;
		i++;
	}
	return (i);
}

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

// int	ft_cnt_dupexport(char **str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		i++;
// 	}
// 	return (i);
// }

// int	main(int ac, char **av, char **env)
// {
// 	(void)ac;
// 	(void)av;
// 	printf("line : %d\n", ft_cntline(env));

// }
