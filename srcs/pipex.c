#include "pipex.h"

void child_process1(char **argv, char *const envp[], int *fd);
void child_process2(char **argv, char *const envp[], int *fd);
void execute(const char *cmdline, char *const envp[]);

int main(int argc, char **argv, char *const envp[])
{
    int fd[2];
    pid_t pid1;
    pid_t pid2;

    if (argc != 5)
    {
        ft_putstr_fd("Usage: ./pipex infile \"cmd1 args\" \"cmd2 args\" outfile\n", 2);
        return (1);
    }

    if (pipe(fd) == -1)
        error("pipe");

    pid1 = fork();
    if (pid1 < 0)
        error("fork #1");
    if (pid1 == 0)
    {
        child_process1(argv, envp, fd);
        error127("child1");
    }

    pid2 = fork();
    if (pid2 < 0)
        error("fork #2");
    if (pid2 == 0)
    {
        child_process2(argv, envp, fd);
        error127("child2");
    }

    close(fd[0]);
    close(fd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return (0);
}

void child_process1(char **argv, char *const envp[], int *fd)
{
    int infile_fd;

    infile_fd = open(argv[1], O_RDONLY);
    if (infile_fd < 0)
        error("open failure");
    if (dup2(infile_fd, STDIN_FILENO) == -1)
        error("dup2 infile -> stdin");
    if (dup2(fd[1], STDOUT_FILENO) == -1)
        error("dup2 pipe[1] -> stdout");
    close(infile_fd);
    close(fd[0]);
    close(fd[1]);
    c(argv[2], envp);
}

void child_process2(char **argv, char *const envp[], int *fd)
{
    int outfile_fd;

    outfile_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (outfile_fd < 0)
        error("open failure");
    if (dup2(fd[0], STDIN_FILENO) == -1)
        error("dup2 pipe[0] -> stdin");
    if (dup2(outfile_fd, STDOUT_FILENO) == -1)
        error("dup2 outfile -> stdout");
    close(outfile_fd);
    close(fd[1]);
    close(fd[0]);

    execute(argv[3], envp);
}

void execute(const char *cmdline, char *const envp[])
{
    char **cmd;
    char *path;

    cmd = ft_split(cmdline, ' ');
    if (!cmd || !cmd[0])
    {
        ft_putstr_fd("pipex: command not found\n", 2);
        free_split(cmd);
        error127("cmd split");
    }
    if (ft_strchr(cmd[0], '/')) {
        execve(cmd[0], cmd, envp);
        free_split(cmd);
        error127("execve");
    }
    path = find_path(cmd[0], envp);
    if (path)
    {
        execve(path, cmd, envp);
        free(path);
        free_split(cmd);
        error127("execve");
    }
    ft_putstr_fd("pipex: command not found\n", 2);
    free_split(cmd);
    error127("execve");
}
