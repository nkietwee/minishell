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

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	init_minishell(t_minishell	*ms, int *ac, char ***av, char ***env)
{
	(void)*ac;
	(void)*av;
	ms->tk_lst = NULL;
	ms->tb_lst = NULL;
	ms->dict = NULL;
	ms->index = 0;
	ms->err_code = 0;
	ms->exit_code = 0;
	ms->env = *env;
	ms->sigint.sa_handler = sig_handler;
	sigemptyset(&ms->sigint.sa_mask);
	ms->sigint.sa_flags = SA_RESTART;
	sigaction(SIGINT, &ms->sigint, NULL);
	ms->sigquit.sa_handler = SIG_IGN;
	sigemptyset(&ms->sigquit.sa_mask);
	ms->sigquit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &ms->sigquit, NULL);
}

void	clear_tb_n_tk(t_minishell *ms)
{
	t_list	*tb_lst;
	t_table	*table;

	ft_lstclear(&ms->tk_lst, &free);
	tb_lst = ms->tb_lst;
	while (tb_lst)
	{
		table = tb_lst->data;
		if (table->rdr)
			ft_lstclear(&table->rdr, &free);
		tb_lst = tb_lst->next;
	}
	ft_lstclear(&ms->tb_lst, &free);
	ms->tk_lst = NULL;
	ms->tb_lst = NULL;
}

void	clear_minishell(t_minishell *ms)
{
	rl_clear_history();
	if (ms->dict)
		free_dict(ms->dict);
	clear_tb_n_tk(ms);
}

int	main(int ac, char **av, char **env)
{
	char		*line;
	char		*prompt_str;
	t_minishell	ms;

	init_minishell(&ms, &ac, &av, &env);
	ms.dict = ft_getenv(env);
	while (1)
	{
		prompt_str = prompt();
		line = readline(prompt_str);
		free(prompt_str);
		if (line == NULL)
			break ;
		if (check_line(line))
			continue ;
		add_history(line);
		if (lexer(line, &ms))
			continue ;
		if (paser(&ms))
			continue ;
		ft_mainexec(&ms);
		clear_tb_n_tk(&ms);
	}
	clear_minishell(&ms);
	return (printf("exit\n"), 0);
}
