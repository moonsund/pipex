#include "pipex.h"

int usage(int argc, char **argv)
{
    if (argc < 5)
    {
        ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 [cmd3 ... cmdN] outfile\n"
                     "   or: ./pipex here_doc LIMITER cmd1 [cmd2 ... cmdN] outfile\n", 2);
        return (1);
    }
    if (ft_strncmp(argv[1], "here_doc", 9) == 0 && argc < 6)
    {
        ft_putstr_fd("Usage: ./pipex here_doc LIMITER cmd1 cmd2 [cmd3 ... cmdN] outfile\n", 2);
        return (1);
    }
    return (0);
}