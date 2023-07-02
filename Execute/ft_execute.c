
#include "../Include/minishell.h"

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	// printf("env : %s\n" , env[2]);
	// printf("Hello World! From Milo EiEi\n");
	// printf("minishell is bug laewwwwwwww Fix it now\n");
	char *tmp=NULL;
	
	// int i = 0;
	while (1)
	{
		tmp = readline(BLU"nkietwee % "RESET);
		if (!tmp)
			return (0);
		add_history(tmp);
		// printf("history : %d\n" ,add_history(tmp));
		// printf("cmd : %s\n" ,tmp);
		if (ft_strlen(tmp) > 0)
			ft_main(tmp, env);
			// ft_initdata();
			
		free(tmp);
	}
}