/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorlov <lorlov@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 15:33:32 by lorlov            #+#    #+#             */
/*   Updated: 2025/09/23 18:21:25 by lorlov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void here_doc(const char *limiter)
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
                (line[l_len] == '\0' || line[l_len] == '\n'))
                {
                    free(line);
                    close(fd[1]);
                    exit(EXIT_SUCCESS);
                }
            write(fd[1], line, ft_strlen(line));
            free(line);
            line = get_next_line(STDIN_FILENO);
        }
    }
    close(fd[1]);
    if (dup2(fd[0], STDIN_FILENO) == -1)
        error("here_doc dup2 fd[0] -> stdin");
    close(fd[0]);
    waitpid(reader, NULL, 0);
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
        if (dup2(fd[1], STDOUT_FILENO) == -1)
            error("dup2 fd[1] -> stdout");
        close(fd[1]);
        execute(cmdline, envp);
    }
    close(fd[1]);
    if (dup2(fd[0], STDIN_FILENO) == -1)
        error("dup2 fd[0] -> stdin");
    close(fd[0]);
}