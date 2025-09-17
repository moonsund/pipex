/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorlov <lorlov@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 15:33:10 by lorlov            #+#    #+#             */
/*   Updated: 2025/09/17 09:19:25 by lorlov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <stdbool.h>
#include <stddef.h>
# include <fcntl.h>    // open
# include <unistd.h>   // close, pipe, fork, read, write
# include <fcntl.h>    // read flags
# include <stdio.h>    // perror, printf
# include <sys/stat.h> // fstat, struct stat
# include <errno.h>    // errno

// typedef struct s_cmd
// {
//     char **argv_cmd;
//     char *full_path;
//     int has_slash;
//     int status;
// } t_cmd;

// typedef struct s_pipex
// {
//     int fd_in;
//     int fd_out;
//     bool append_mode;
//     const char *infile;
//     const char *outfile;
//     const char *limiter;
//     int cmd_count;
//     char **raw_cmdv;
//     t_cmd **cmdv;
//     char **envp;
// }   t_pipex;



// utils.c
char    *find_path(char *cmd, char *const envp[]);
void    error(const char *msg);
void error127(const char *msg);
void exec_error_exit(const char *cmd);
void    free_split(char **array);


// bool init_files(t_pipex *p, int argc, char **argv);

// void check_commands(t_pipex *p, char **envp);






#endif