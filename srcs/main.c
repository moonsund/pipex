#include "pipex.h"

int main(int argc, char **argv, char *const envp[])
{
    if (argc != 5)
    {
        ft_putstr_fd("Usage: ./pipex infile \"cmd1 args\" \"cmd2 args\" outfile\n", 2);
        return (1);
    }
    return run_pipeline(argv, envp);
}
