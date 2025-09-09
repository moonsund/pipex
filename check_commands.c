/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorlov <lorlov@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:16:48 by lorlov            #+#    #+#             */
/*   Updated: 2025/09/09 13:58:27 by lorlov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void check_commands(t_pipex *p, char **envp)
{

    int i = 0;
    while (i < p->cmdc)
    {
        if (ft_strchr(p->cmdv[i], '/'))
        {
            if (access(p->cmdv[i], F_OK | X_OK) == 0)
                printf("надо куда то сохранить результат");
            else
                perror("Нет прав на выполнение");
        }

        else
        {
            int i = 0;
            while (envp[i])
            {
                
            }
                printf("%s\n", envp[i++]);
            // берем PATH из envp с помощью ft_strncmp;
            // Разбиваем PATH по «:» с помощью ft_split;
            // разбиваем команду на тело и возможный флаг с помощью ft_split;
            // проверяем есть ли исполняемый файл в каком то каталоге для проверяемой команды с помощью access;
            // если есть, склеиваем строку из пути каталога, команды и ее флага с помощью ft_strjoin
        }
        i++;
    }
    



    
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