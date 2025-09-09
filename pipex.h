/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorlov <lorlov@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 15:33:10 by lorlov            #+#    #+#             */
/*   Updated: 2025/09/09 13:52:58 by lorlov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <stdbool.h>
# include <fcntl.h>    // open
# include <unistd.h>   // close, pipe, fork, read, write
# include <stdio.h>    // perror, printf
# include <sys/stat.h> // fstat, struct stat
# include <errno.h>    // errno

typedef struct s_pipex
{
    int fd_in;
    int fd_out;
    bool append_mode;
    const char *infile;
    const char *outfile;
    const char *limiter;
    int cmdc;
    char **cmdv;
    char **envp;
}   t_pipex;

bool init_files(t_pipex *p, int argc, char **argv);

void check_commands(t_pipex *p, char **envp);






#endif