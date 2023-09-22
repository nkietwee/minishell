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


void	ft_initdata(t_minishell *ms, char **env)
{
	// ms->data = NULL;
	// printf("init_data\n");
	ms->data.fd_in = 0;
	ms->data.fd_out = 0;
	ms->data.fd_tmp_read = 0;
	ms->data.fd_pipe[0] = 0;
	ms->data.fd_pipe[1] = 0;
	ms->data.nbr_infile = 0;
	ms->data.nbr_out_append = 0;
	ms->data.nbr_cmd = 0;
	ms->data.nbr_heredoc = 0;
	ms->data.fd_heredoc = 0;
	ms->data.tmp_env = env;
	ms->data.path = NULL;

	// ms->dict = ft_getenv(env);
	// exit (0);

}
int main(int ac, char **av, char **env)
{
	char 		*line;
	char 		*prompt_str;
	t_minishell	ms;

	// int i = ms.data.fd_in = 0;
	// printf("i : %d\n", i);
	ft_initdata(&ms, env);
	// exit(0);
	(void)ac;
	(void)av;
	(void)env;
	while (1)
	{
		// รับ signal ใน while loop
		prompt_str = prompt();
		line = readline(prompt_str); // รับค่า control d ผ่าน readline
		free (prompt_str);
		if (!line)
			return (1);
		add_history(line);
		if(lexer(line, &ms))
			continue ;
		// print_token(ms);
		paser(&ms);
		// print_table(ms);
		ft_mainexec(&ms);
		// excute(&ms); รับ signal ใน while loop
		// free_token(&ms.token);
	}
	// free_token(&ms.token); exit print
	free(&line);
	free(&ms);
	return (0);
}