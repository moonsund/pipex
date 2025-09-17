/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorlov <lorlov@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:16:48 by lorlov            #+#    #+#             */
/*   Updated: 2025/09/16 17:09:53 by lorlov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void check_commands(t_pipex *p, char **envp)
{
    int i = 0;

    while (i < p->cmd_count)
    {
        p->cmdv[i] = malloc(sizeof(t_cmd));
        if (ft_strchr(p->raw_cmdv[i], '/'))
        {
            if (access(p->raw_cmdv[i], F_OK | X_OK) == 0)
            {
                p->cmdv[i]->full_path = p->raw_cmdv[i];
                p->cmdv[i]->argv_cmd = NULL;
                p->cmdv[i]->has_slash = 1;
                p->cmdv[i]->status = 1;
            }
            else
            {
                perror("zsh:");
                p->cmdv[i]->full_path = p->raw_cmdv[i];
                p->cmdv[i]->argv_cmd = NULL;
                p->cmdv[i]->has_slash = 1;
                p->cmdv[i]->status = 0;
            }
        }
        else
        {
            p->cmdv[i]->status = 0;
            p->cmdv[i]->argv_cmd = ft_split(p->raw_cmdv[i], ' ');
            int j = 0;
            while (envp[j])
            {
                if (ft_strncmp(envp[j], "PATH=", 5) == 0)
                {
                    char **splited_path = ft_split(envp[j] + 5, ':');
                    int k = 0;
                    while (splited_path[k])
                    {
                        char *str = ft_strjoin(splited_path[k], "/");
                        str = ft_strjoin(str, p->cmdv[i]->argv_cmd[0]);
                        if (access(str, F_OK | X_OK) == 0)
                        {
                            // printf("PATH: %s\n", str);
                            p->cmdv[i]->argv_cmd = &str;
                            break;
                        }
                        k++;
                    }
                }
                j++;
            }
        }
        i++;
    }

    
    

    // typedef struct s_cmd
    // {
    //     char **argv_cmd;
    //     char *full_path;
    //     int has_slash;
    //     int status;
    // } t_cmd;


    
// char *path;


// path = getenv("PATH");
// if (!path)
    

    // int i = 0;
    // while (envp[i])
    //     printf("%s\n", envp[i++]);

//     char *path = getenv("PATH");
//     printf("XXXX PATH: %s\n", path);

// printf("XXXX PATH: %s\n", path);
}


// typedef struct s_pipex
// {
//     int fd_in;
//     int fd_out;
//     bool append_mode;
//     const char *infile;
//     const char *outfile;
//     const char *limiter;
//     int cmdc;
//     char **cmdv;
//     char **envp;
// }   t_pipex;