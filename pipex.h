/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorlov <lorlov@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 15:33:10 by lorlov            #+#    #+#             */
/*   Updated: 2025/09/23 19:29:04 by lorlov           ###   ########.fr       */
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
void    error(const char *msg);
void error127(const char *msg);
void    free_split(char **array);

// pipiex_bous
void here_doc(const char *limiter);
void child_process(const char *cmdline, char *const envp[]);

// utils_bonus.c
int usage(int argc, char **argv);

#endif