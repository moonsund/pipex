/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorlov <lorlov@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 15:33:32 by lorlov            #+#    #+#             */
/*   Updated: 2025/09/24 11:47:24 by lorlov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void here_doc(const char *limiter);
static void write_until_limiter(int wr_fd, const char *limiter);

void run_append_mode(int argc, char **argv, int *cmd_position, int *outfile_fd)
{
    *cmd_position = 3;
    *outfile_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (*outfile_fd < 0)
        sys_call_error("open outfile failure");
    here_doc(argv[2]);
}

void run_trunc_mode(int argc, char **argv, int *cmd_position, int *infile_fd, int *outfile_fd)
{
    int devnull;
    
    *cmd_position = 2;
    *infile_fd = open(argv[1], O_RDONLY);
    if (infile_fd < 0)
    {
        perror("open infile failure");
        devnull = open("/dev/null", O_RDONLY);
        if (devnull < 0)
            sys_call_error("open /dev/null failure");
        if (dup2(devnull, STDIN_FILENO) == -1)
            sys_call_error("dup2 /dev/null -> stdin");
        close(devnull);
    }
    else
    {
        if (dup2(*infile_fd, STDIN_FILENO) == -1)
            sys_call_error("dup2 infile_fd -> stdin");
        close(*infile_fd);
    }  
    *outfile_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (outfile_fd < 0)
        sys_call_error("open outfile failure");    
}

static void here_doc(const char *limiter)
{
    int fd[2];
    pid_t reader;

    if (pipe(fd) == -1)
        sys_call_error("here_doc pipe");
    reader = fork();
    if (reader < 0)
        sys_call_error("fork reader");
        
    if (reader == 0)
    {
        close(fd[0]);
        write_until_limiter(fd[1], limiter);
        close(fd[1]);
        exit(EXIT_SUCCESS);
    }
    close(fd[1]);
    if (dup2(fd[0], STDIN_FILENO) == -1)
        sys_call_error("here_doc dup2 fd[0] -> stdin");
    close(fd[0]);
    waitpid(reader, NULL, 0);
}

static void write_until_limiter(int wr_fd, const char *limiter)
{
    size_t l_len;
    char *line;
    
    l_len = ft_strlen(limiter);
    line = get_next_line(STDIN_FILENO);
    while (line)
    {
        if (ft_strncmp(line, limiter, l_len) == 0 &&
            (line[l_len] == '\0' || line[l_len] == '\n'))
            {
                free(line);
                return;
            }
        write(wr_fd, line, ft_strlen(line));
        free(line);
        line = get_next_line(STDIN_FILENO);
    }
}

void child_process(const char *cmdline, char *const envp[])
{
    pid_t pid;
    int   fd[2];

    if (pipe(fd) == -1)
        sys_call_error("pipe cmd");
    pid = fork();
    if (pid < 0)
        sys_call_error("fork cmd");
    if (pid == 0)
    {
        close(fd[0]);
        if (dup2(fd[1], STDOUT_FILENO) == -1)
            sys_call_error("dup2 fd[1] -> stdout");
        close(fd[1]);
        execute(cmdline, envp);
    }
    close(fd[1]);
    if (dup2(fd[0], STDIN_FILENO) == -1)
        sys_call_error("dup2 fd[0] -> stdin");
    close(fd[0]);
}