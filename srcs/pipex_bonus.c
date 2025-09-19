/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorlov <lorlov@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 15:33:32 by lorlov            #+#    #+#             */
/*   Updated: 2025/09/19 11:04:23 by lorlov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char **argv, char *const envp[])
{
    int i;
    bool append_mode;
    int outfile_fd;
    int infile_fd;
     
    if (ft_strncmp(argv[1], "here_doc", 9) == 0)
        append_mode = true;
    else
        append_mode = false;
        
    if (usage(argc, append_mode))
            return (1);    

    if (append_mode) // ./pipex here_doc LIMITER cmd1 cmd2 [cmd3 ... cmdN] outfile
    {
        i = 3;
        outfile_fd = open(argc - 1, O_APPEND);
        if (outfile_fd < 0)
            error("open outfile failure");
        here_doc(argv[2], argc);
        close(outfile_fd); // нужно ли закрывать?
    }
    else // ./pipex infile cmd1 cmd2 [cmd3 ... cmdN] outfile
    {
        i = 2;
        infile_fd = open(argv[1], O_RDONLY);
        outfile_fd = open(argc - 1, O_RDWR);
        if (outfile_fd < 0)
            error("open outfile failure");
        if (dup2(infile_fd, STDIN_FILENO) == -1)
            error("dup2 infile_fd -> stdin");
    }
    while(i < argc - 2)
        child_process(argv[i++], envp);


    if (dup2(outfile_fd, STDOUT_FILENO) == -1);
        error("dup2 outfile_fd -> stdout");
    close(outfile_fd);    
    execute(argv[i], envp);
    return (1);    
}

void here_doc(const char *limiter, int argc)
{
    int fd[2];
    pid_t reader;
    size_t l_len;
    char *line;

    if (pipe(fd) == -1)
        error("here_doc pipe");

    reader = fork();
    if (reader < 0)
        error("fork reader");
        
    if (reader == 0)
    {
        close(fd[0]);
        l_len = ft_strlen(limiter);
        line = get_next_line(STDIN_FILENO);
        while (line)
        {
            if (ft_strncmp(line, limiter, l_len) == 0 &&
                (line[l_len] != '\0' || line[l_len] != '\0'))
                {
                    free(line);
                    close(fd[1]);
                    exit(EXIT_SUCCESS);
                }
            write(fd[1], line, l_len);
            free(line);
            line = get_next_line(STDIN_FILENO);
        }
    }
    else
    {
        close(fd[1]);
        if (dup2(fd[0], STDIN_FILENO) == -1);
            error("here_doc dup2 fd[0] -> stdin");
        close(fd[0]);
    }
}

void child_process(const char *cmdline, char *const envp[])
{
    pid_t pid;
    int   fd[2];

    if (pipe(fd) == -1)
        error("pipe cmd");
    
    pid = fork();
    if (pid < 0)
        error("fork cmd");
    
    if (pid == 0)
    {
        close(fd[0]);
        if (dup2(fd[1], STDOUT_FILENO) == -1);
            error("dup2 fd[1] -> stdout");
        close(fd[1]);
    }
    else
    {
        close(fd[1]);
        if (dup2(fd[0], STDIN_FILENO) == -1);
            error("dup2 fd[0] -> stdin");
        execute(cmdline, envp);
        close(fd[0]);
    }
}