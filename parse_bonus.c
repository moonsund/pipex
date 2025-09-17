/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorlov <lorlov@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 18:38:59 by lorlov            #+#    #+#             */
/*   Updated: 2025/09/09 11:01:44 by lorlov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static bool open_infile(t_pipex *pipex);
static bool open_outfile(t_pipex *pipex);
static void safe_close(int *p);
static bool open_devnull(int *fd);

bool init_files(t_pipex *p, int argc, char **argv)
{
    p->fd_in = -1;
    p->fd_out = -1;
    if (!p->append_mode)
    {
        if (!open_infile(p))
        {
            if (!open_devnull(&p->fd_in))
                return (false);
        }
    }
    if (!open_outfile(p))
        return (false);  
    return (true);
}

static bool open_infile(t_pipex *p)
{
    struct stat st;

    p->fd_in = open(p->infile, O_RDONLY);
    if (p->fd_in == -1)
    {
        perror(p->infile); 
        return (false);
    }
    if (fstat(p->fd_in, &st) == -1)
    {
        perror("fstat");
        safe_close(&p->fd_in);
        return (false);
    }
    if (S_ISDIR(st.st_mode))
    {
        errno = EISDIR;
        perror(p->infile);
        safe_close(&p->fd_in);
        return (false);
    }
    return (true);
}

static bool open_outfile(t_pipex *p)
{   
    if (p->append_mode)
        p->fd_out = open(p->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
    else
        p->fd_out = open(p->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (p->fd_out == -1)
    {
        perror(p->outfile);
        safe_close(&p->fd_in);
        return (false);
    }
    return (true);
}

static void safe_close(int *p)
{
    if (p && *p != -1)
    {
        close(*p);
        *p = -1;
    }
}

static bool open_devnull(int *fd)
{
    int fd_tmp;
    fd_tmp = open("/dev/null", O_RDONLY);
    if (fd_tmp < 0)
        {
            perror("/dev/null");
            return (false);
        }
    *fd=fd_tmp;
    return (true);
}