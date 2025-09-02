/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorlov <lorlov@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 15:33:10 by lorlov            #+#    #+#             */
/*   Updated: 2025/08/23 13:13:13 by lorlov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <stdbool.h>
# include <fcntl.h>    // open
# include <unistd.h>   // close
# include <stdio.h>    // perror, printf
# include <sys/stat.h> // fstat, struct stat
# include <errno.h>    // errno

typedef struct s_pipex
{
    const char *infile;
    const char *outfile;
    char *cmd1;
    char *cmd2;
    char **envp;
    bool here_doc;
    bool append_mode;
    int fd_in;
    int fd_out;
}   t_pipex;

bool init_files(t_pipex *p, int argc, char **argv);







#endif