/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorlov <lorlov@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 15:33:10 by lorlov            #+#    #+#             */
/*   Updated: 2025/09/24 11:48:31 by lorlov           ###   ########.fr       */
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

// pipex.c
int run_pipeline(char **argv, char *const envp[]);
void execute(const char *cmdline, char *const envp[]);

// utils.c
char    *find_path(char *cmd, char *const envp[]);
void    sys_call_error(const char *msg);
void cmd_exec_error(const char *msg);
void    free_split(char **array);

// pipiex_bonus
void run_append_mode(int argc, char **argv, int *cmd_position, int *outfile_fd);
void run_trunc_mode(int argc, char **argv, int *cmd_position, int *infile_fd, int *outfile_fd);
void child_process(const char *cmdline, char *const envp[]);

// utils_bonus.c
int usage(int argc, char **argv);

#endif