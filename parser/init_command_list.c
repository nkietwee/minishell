/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_command_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 13:52:18 by ptungbun          #+#    #+#             */
/*   Updated: 2023/09/17 02:30:51 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	slide_n_decide(t_list *lst, char *line)
{
	while (*line)
	{
		if (lst == NULL)
			return (0);
		else if (ft_isquote(*line))
			return (2);
		else if (ft_ismetachar(*line))
			return (3);
		else if (!ft_isspace(*line))
			return (1);
		line++;
	}
	return (-1);
}

void	print_lst(t_list *lst)
{
	while(lst)
	{
		printf("token->str = %s\n", ((t_token*)lst->data)->str);
		lst = lst->next;
	}
}

int	init_command_list(t_minishell **ms, char *line)
{
	t_list	*lst;
	char	*ptr_line;
	int		index;

	ptr_line = line;
	lst = NULL;
	while (*ptr_line)
	{
		index = slide_n_decide(lst, ptr_line);
		if (index == -1)
			return (1);
		grab_to_lst(&lst, &ptr_line, index);
		print_lst(lst);
	}
	(*ms)->lst = lst;
	return (0);
}
