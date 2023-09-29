/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptungbun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 18:44:05 by ptungbun          #+#    #+#             */
/*   Updated: 2023/07/11 18:44:19 by ptungbun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	print_table(t_minishell ms)
{
	t_list	*tb_lst;
	t_list	*rdr_lst;
	t_rdr	*rdr;
	t_table	*table;
	int		i;

	tb_lst = ms.tb_lst;
	while (tb_lst)
	{
		table = tb_lst->data;
		rdr_lst = table->rdr;
		i = 0;
		printf("----cmd----\n");
		while ((table->cmd)[i])
		{
			printf("table->cmd[%d] = %s\n", i, (table->cmd)[i]);
			i++;
		}
		printf("----rdr----\n");
		rdr_lst = table->rdr;
		while (rdr_lst)
		{
			rdr = rdr_lst->data;
			if(rdr)
			{
				printf("rdr->file = %s\n", rdr->file);
				printf("rdr->type = %d\n", rdr->type);
			}
			rdr_lst = rdr_lst->next;
		}
		printf("----next table----\n");
		tb_lst = tb_lst->next;
	}
}

static void	print_token(t_minishell ms)
{
	t_list	*token_lst;
	t_token	*token;

	token_lst = ms.tk_lst;
	printf("----token----\n");
	while(token_lst)
	{
		token = token_lst->data;
		printf("token->str = %s\n", token->str);
		printf("token->type = %d\n", token->type);
		token_lst = token_lst->next;
	}
}

int main(int ac, char **av, char **env)
{
	char 		*line;
	char 		*prompt_str;
	t_minishell	ms;

	// init_minishell(&ms, env, &ac, &av);
	(void)ac;
	(void)av;
	(void)env;
	ms.env = env;
	while (1)
	{
		// dprintf(1 ,"c_11\n");
		prompt_str = prompt();
		// dprintf(1 ,"c_12\n");
		line = readline(prompt_str);
		// dprintf(1 ,"c_13\n");
		free(prompt_str);
		// dprintf(1 ,"c_14\n");
		if ( !*line || !line)
		{
			// free(line);
			continue ;
		}
		// dprintf(1 ,"c_15\n");
		add_history(line);
		// dprintf(1 ,"c_16\n");
		if(lexer(line, &ms))
			continue ;
		// print_token(ms);
		// dprintf(1 ,"c_17\n");
		// free(line);
		if (paser(&ms))
		{
			// clear_n_init_ms(&ms);
			continue;
		}
		// dprintf(1 ,"c_18\n");
		// print_table(ms);
		ft_mainexec(&ms);
		// dprintf(1 ,"main\n");
		// clear_n_init_ms(&ms);
	}
	return (0);
}
