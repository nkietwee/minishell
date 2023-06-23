
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
        tmp = readline("Name ");
        // tmp = readline 
        if (!tmp)
            return (0);
        printf("%s\n" ,tmp);
        free(tmp);
        // i = readline("Name");
    }
}