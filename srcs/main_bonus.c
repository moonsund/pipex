/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorlov <lorlov@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 15:33:32 by lorlov            #+#    #+#             */
/*   Updated: 2025/09/24 10:38:21 by lorlov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char **argv, char *const envp[])
{
    int cmd_position;
    int outfile_fd;
    int infile_fd;
        
    if (usage(argc, argv))
            return (1);
    if (ft_strncmp(argv[1], "here_doc", 9) == 0)
        run_append_mode(argc, argv, &cmd_position, &outfile_fd);
    else
        run_trunc_mode(argc, argv, &cmd_position, &infile_fd, &outfile_fd);
    while(cmd_position < argc - 2)
        child_process(argv[cmd_position++], envp);
    if (dup2(outfile_fd, STDOUT_FILENO) == -1)
        sys_call_error("dup2 outfile_fd -> stdout");
    close(outfile_fd);    
    execute(argv[cmd_position], envp);
    return (0);    
}