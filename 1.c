#include "pipex.h"

int main(int argc, char **argv, char *const envp[])
{
    int cmd_position;
    int outfile_fd;
    int infile_fd;
    int devnull;
        
    if (usage(argc, argv))
            return (1);    
    if (ft_strncmp(argv[1], "here_doc", 9) == 0) // ./pipex here_doc LIMITER cmd1 cmd2 [cmd3 ... cmdN] outfile
    {
        cmd_position = 3;
        outfile_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (outfile_fd < 0)
            error("open outfile failure");
        here_doc(argv[2]);
    }
    else // ./pipex infile cmd1 cmd2 [cmd3 ... cmdN] outfile
    {
        cmd_position = 2;
        infile_fd = open(argv[1], O_RDONLY);
        if (infile_fd < 0)
        {
            perror("open infile failure");
            devnull = open("/dev/null", O_RDONLY);
            if (devnull < 0)
                error("open /dev/null");
            if (dup2(devnull, STDIN_FILENO) == -1)
                error("dup2 /dev/null -> stdin");
            close(devnull);
        }
        else
        {
            if (dup2(infile_fd, STDIN_FILENO) == -1)
                error("dup2 infile_fd -> stdin");
            close(infile_fd);
        }  
        outfile_fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (outfile_fd < 0)
            error("open outfile failure");    
    }
    while(cmd_position < argc - 2)
        child_process(argv[cmd_position++], envp);
    if (dup2(outfile_fd, STDOUT_FILENO) == -1)
        error("dup2 outfile_fd -> stdout");
    close(outfile_fd);    
    execute(argv[cmd_position], envp);
    return (0);    
}

void here_doc(const char *limiter)
{
    int fd[2];
    pid_t reader;
    size_t l_len;
    char *line;

    if (pipe(fd) == -1)
        error("here_doc pipe");

    reader = fork();
    if (reader < 0)
        error("fork reader");
        
    if (reader == 0)
    {
        close(fd[0]);
        l_len = ft_strlen(limiter);
        line = get_next_line(STDIN_FILENO);
        while (line)
        {
            if (ft_strncmp(line, limiter, l_len) == 0 &&
                (line[l_len] == '\0' || line[l_len] == '\n'))
                {
                    free(line);
                    close(fd[1]);
                    exit(EXIT_SUCCESS);
                }
            write(fd[1], line, ft_strlen(line));
            free(line);
            line = get_next_line(STDIN_FILENO);
        }
    }
    close(fd[1]);
    if (dup2(fd[0], STDIN_FILENO) == -1)
        error("here_doc dup2 fd[0] -> stdin");
    close(fd[0]);
    waitpid(reader, NULL, 0);
}

void child_process(const char *cmdline, char *const envp[])
{
    pid_t pid;
    int   fd[2];

    if (pipe(fd) == -1)
        error("pipe cmd");
    pid = fork();
    if (pid < 0)
        error("fork cmd");
    if (pid == 0)
    {
        close(fd[0]);
        if (dup2(fd[1], STDOUT_FILENO) == -1)
            error("dup2 fd[1] -> stdout");
        close(fd[1]);
        execute(cmdline, envp);
    }
    close(fd[1]);
    if (dup2(fd[0], STDIN_FILENO) == -1)
        error("dup2 fd[0] -> stdin");
    close(fd[0]);
}



