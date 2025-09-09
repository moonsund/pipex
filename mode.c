#include "pipex.h"

bool set_mode_and_bounds(t_pipex *p, int argc, char **argv)
{
    if (argc < 5)
    {
        ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 [cmd3 ... cmdN] outfile\n", 2);
        return (false);
    }
    p->append_mode = (ft_strcmp(argv[1], "here_doc") == 0);
    if (p->append_mode)
    {
        if (argc < 6)
        {
            ft_putstr_fd("Usage: ./pipex here_doc LIMITER cmd1 cmd2 [cmd3 ... cmdN] outfile\n", 2);
            return (false);
        }
        p->infile = NULL;
        p->cmdc = argc - 4;
        p->cmdv = &argv[3];
    }
    else
    {
        p->infile = argv[1]; 
        p->cmdc = argc - 3;
        p->cmdv = &argv[2];
    }
    return (true);
}