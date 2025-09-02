/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorlov <lorlov@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 15:33:32 by lorlov            #+#    #+#             */
/*   Updated: 2025/09/02 10:22:56 by lorlov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char **argv, char **envp)
{
    (void)envp; // удалить позже
    t_pipex pipex;
    
    if (argc < 5)
    {
        ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 [cmd3 ... cmdN] outfile\n", 2);
        return (1);
    }
    if (ft_strcmp(argv[1], "here_doc") == 0 && argc < 6)
    {
        ft_putstr_fd("Usage: ./pipex here_doc LIMITER cmd1 cmd2 [cmd3 ... cmdN] outfile\n", 2);
        return (1);
    }

    
    if (!init_files(&pipex, argc, argv))
    {
        return (1);
    }
    // ... дальше настройка пайпов/форки/execve ...
    // fd_in обычно дуплицируют в stdin первого процесса,
    // fd_out — в stdout последнего. Лишние дескрипторы в детях закрывать.
    char	*line = get_next_line(pipex.fd_in);
	if (!line)
	{
		close(pipex.fd_in);
		ft_putstr_fd("ERROR: file is empty.\n", 2);
		return (false);
	}
    printf("infile.txt: %s\n", line);

    
    if (pipex.fd_in  != -1) 
        close(pipex.fd_in);
    if (pipex.fd_out != -1) 
        close(pipex.fd_out);

        

    return 0;
}