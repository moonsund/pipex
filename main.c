/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorlov <lorlov@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 15:33:32 by lorlov            #+#    #+#             */
/*   Updated: 2025/09/09 13:54:02 by lorlov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static bool set_mode_and_bounds(t_pipex *p, int argc, char **argv);

int main(int argc, char **argv, char **envp)
{
    (void)envp; // удалить позже
    
    t_pipex pipex;

    if (!set_mode_and_bounds(&pipex, argc, argv))
        return (1); 
    if (!init_files(&pipex, argc, argv))
        return (1);
    check_commands(&pipex, envp);


    
    // ... дальше настройка пайпов/форки/execve ...
    // fd_in обычно дуплицируют в stdin первого процесса,
    // fd_out — в stdout последнего. Лишние дескрипторы в детях закрывать.



    
    // char	*line = get_next_line(pipex.fd_in);
	// if (!line)
	// {
	// 	close(pipex.fd_in);
	// 	ft_putstr_fd("ERROR: file is empty or does not exist.\n", 2);
	// 	return (false);
	// }
    // printf("infile.txt: %s\n", line);

    
    // if (pipex.fd_in  != -1) 
    //     close(pipex.fd_in);
    // if (pipex.fd_out != -1) 
    //     close(pipex.fd_out);

        

    return 0;
}

static bool set_mode_and_bounds(t_pipex *p, int argc, char **argv)
{
    if (argc < 5)
    {
        ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 [cmd3 ... cmdN] outfile\n"
                     "   or: ./pipex here_doc LIMITER cmd1 [cmd2 ... cmdN] outfile\n", 2);
        return (false);
    }
    p->append_mode = (ft_strcmp(argv[1], "here_doc") == 0);
    p->outfile = argv[argc - 1];
    if (p->append_mode)
    {
        if (argc < 6)
        {
            ft_putstr_fd("Usage: ./pipex here_doc LIMITER cmd1 cmd2 [cmd3 ... cmdN] outfile\n", 2);
            return (false);
        }
        p->infile = NULL;
        p->limiter = argv[2];
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