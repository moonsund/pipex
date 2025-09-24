#include "pipex.h"

static pid_t child_process1(char **argv, char *const envp[], int *fd);
static pid_t child_process2(char **argv, char *const envp[], int *fd);
void execute(const char *cmdline, char *const envp[]);
static char **parse_cmd(const char *cmdline);

int run_pipeline(char **argv, char *const envp[])
{
    int fd[2];
    pid_t pid1;
    pid_t pid2;
    int st1;
    int st2;

    if (pipe(fd) == -1)
        sys_call_error("pipe");
    pid1 = child_process1(argv, envp, fd);
    pid2 = child_process2(argv, envp, fd);
    close(fd[0]);
    close(fd[1]);
    waitpid(pid1, &st1, 0);
    waitpid(pid2, &st2, 0);
    if (WIFEXITED(st2))    
        return WEXITSTATUS(st2);
    if (WIFSIGNALED(st2))
        return 128 + WTERMSIG(st2);
    return 1;
}

static pid_t child_process1(char **argv, char *const envp[], int *fd)
{
    pid_t pid; 
    int infile_fd;

    pid = fork();
    if (pid < 0)
        sys_call_error("fork #1");
    if (pid == 0)
    {
        infile_fd = open(argv[1], O_RDONLY);
        if (infile_fd < 0)
            sys_call_error("open failure");
        if (dup2(infile_fd, STDIN_FILENO) == -1)
            sys_call_error("dup2 infile -> stdin");
        if (dup2(fd[1], STDOUT_FILENO) == -1)
            sys_call_error("dup2 pipe[1] -> stdout");
        close(infile_fd);
        close(fd[0]);
        close(fd[1]);
        execute(argv[2], envp);
        cmd_exec_error("child1");
    }
    return (pid);
}

static pid_t child_process2(char **argv, char *const envp[], int *fd)
{
    pid_t pid;
    int outfile_fd;

    pid = fork();
    if (pid < 0)
        sys_call_error("fork #2");
    if (pid == 0)
    {
        outfile_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (outfile_fd < 0)
            sys_call_error("open failure");
        if (dup2(fd[0], STDIN_FILENO) == -1)
            sys_call_error("dup2 pipe[0] -> stdin");
        if (dup2(outfile_fd, STDOUT_FILENO) == -1)
            sys_call_error("dup2 outfile -> stdout");
        close(outfile_fd);
        close(fd[1]);
        close(fd[0]);
        execute(argv[3], envp);
        cmd_exec_error("child2");
    }
    return (pid);
}

void execute(const char *cmdline, char *const envp[])
{
    char **cmd;
    char *path;

    cmd = parse_cmd(cmdline);
    if (ft_strchr(cmd[0], '/')) 
    {
        execve(cmd[0], cmd, envp);
        free_split(cmd);
        cmd_exec_error("execve");
    }
    path = find_path(cmd[0], envp);
    if (path)
    {
        execve(path, cmd, envp);
        free(path);
        free_split(cmd);
        cmd_exec_error("execve");
    }
    ft_putstr_fd("pipex: command not found\n", 2);
    free_split(cmd);
    exit(127);
}
    
static char **parse_cmd(const char *cmdline)
{
    char **cmd = ft_split(cmdline, ' ');
    if (!cmd || !cmd[0] || cmd[0][0] == '\0')
    {
        ft_putstr_fd("pipex: command not found\n", 2);
        free_split(cmd);
        exit(127);
    }
    return cmd;
}