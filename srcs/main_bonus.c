/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorlov <lorlov@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 15:33:32 by lorlov            #+#    #+#             */
/*   Updated: 2025/09/19 17:55:47 by lorlov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char **argv, char *const envp[])
{
    int i;
    int outfile_fd;
    int infile_fd;
        
    if (usage(argc, argv))
            return (1);    

    if (ft_strncmp(argv[1], "here_doc", 9) == 0) // ./pipex here_doc LIMITER cmd1 cmd2 [cmd3 ... cmdN] outfile
    {
        i = 3;
        outfile_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (outfile_fd < 0)
            error("open outfile failure");
        here_doc(argv[2]);
        close(outfile_fd); // нужно ли закрывать?
    }
    else // ./pipex infile cmd1 cmd2 [cmd3 ... cmdN] outfile
    {
        i = 2;
        infile_fd = open(argv[1], O_RDONLY);
        outfile_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (outfile_fd < 0)
            error("open outfile failure");
        if (dup2(infile_fd, STDIN_FILENO) == -1)
            error("dup2 infile_fd -> stdin");
    }
    while(i < argc - 2)
        child_process(argv[i++], envp);


    if (dup2(outfile_fd, STDOUT_FILENO) == -1)
        error("dup2 outfile_fd -> stdout");
    close(outfile_fd);    
    execute(argv[i], envp);
    return (1);    
}