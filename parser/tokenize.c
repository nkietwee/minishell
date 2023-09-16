/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:59:50 by ptungbun          #+#    #+#             */
/*   Updated: 2023/09/17 02:31:16 by nkietwee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	search_start(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\'' || str[i] == '\"')
		i++;
	if (ft_ismetachar(str[i]))
	{
		if (str[i] == '>' && str[i + 1] == '>')
			return (APBFCMD);
		if (str[i] == '>')
			return (OFBFCMD);
		if (str[i] == '<' && str[i + 1] == '<')
			return (HDBFCMD);
		if (str[i] == '<')
			return (IFBFCMD);
	}
	return (CMD);
}

static int	search_empty(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\'' || str[i] == '\"')
		i++;
	if (ft_ismetachar(str[i]))
	{
		if (str[i] == '|')
			return (PIPE);
		if (str[i] == '>' && str[i + 1] == '>')
			return (APPEND);
		if (str[i] == '>')
			return (OUTFILE);
		if (str[i] == '<' && str[i + 1] == '<')
			return (HEREDOC);
		if (str[i] == '<')
			return (INFILE);
	}
	return (ARG);
}

static int	tag_token(int *tag_ctrl)
{
	int	temp;

	if (*tag_ctrl == CMD)
	{
		*tag_ctrl = EMPTY;
		return (CMD);
	}
	else if (*tag_ctrl == ARG)
	{
		*tag_ctrl = EMPTY;
		return (ARG);
	}
	else if (*tag_ctrl == HEREDOC || *tag_ctrl == INFILE \
	|| *tag_ctrl == OUTFILE || *tag_ctrl == APPEND)
	{
		temp = *tag_ctrl;
		*tag_ctrl = FPATH;
		return (temp);
	}
	else if (*tag_ctrl == PIPE)
	{
		*tag_ctrl = START;
		return (PIPE);
	}
	else if (*tag_ctrl == FPATH)
	{
		*tag_ctrl = EMPTY;
		return (FPATH);
	}
	return (0);
}

static int	tag_token_start(int *tag_ctrl)
{
	if (*tag_ctrl == IFBFCMD)
	{
		*tag_ctrl = FPBFCMD;
		return (INFILE);
	}
	if (*tag_ctrl == OFBFCMD)
	{
		*tag_ctrl = FPBFCMD;
		return (OUTFILE);
	}
	if (*tag_ctrl == HDBFCMD)
	{
		*tag_ctrl = FPBFCMD;
		return (HEREDOC);
	}
	if (*tag_ctrl == APBFCMD)
	{
		*tag_ctrl = FPBFCMD;
		return (APPEND);
	}
	if (*tag_ctrl == FPBFCMD)
	{
		*tag_ctrl = CMD;
		return (FPATH);
	}
	if (*tag_ctrl == CMD)
		*tag_ctrl = EMPTY;
	return (CMD);
}

int	tokenize(t_minishell **ms)
{
	t_list	*lst;
	int		tag_ctrl;

	if(!ms)
		return(1);
	lst = (*ms)->lst;
	tag_ctrl = START;
	while(lst)
	{
		if (tag_ctrl == START || tag_ctrl == FPBFCMD)
		{
			if (tag_ctrl == START)
				tag_ctrl = search_start(((t_token *)lst->data)->str);
			((t_token *)lst->data)->type = tag_token_start(&tag_ctrl);
		}
		else
		{
			if (tag_ctrl == EMPTY)
				tag_ctrl = search_empty(((t_token *)lst->data)->str);
			((t_token *)lst->data)->type = tag_token(&tag_ctrl);
		}
		// printf("tag = %d\n", ((t_token *)lst->data)->type);
		// printf("str = %s\n", ((t_token *)lst->data)->str);
		lst = lst->next;
	}
	return(0);
}
