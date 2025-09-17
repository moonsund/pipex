static void cmd_not_found(const char *name)
{
    if (name && *name)
        ft_putstr_fd("pipex: ", 2), ft_putstr_fd(name, 2), ft_putstr_fd(": command not found\n", 2);
    else
        ft_putstr_fd("pipex: command not found\n", 2);
}

void execute(const char *cmdline, char *const envp[])
{
    char **cmd = ft_split(cmdline, ' ');
    if (!cmd || !cmd[0] || cmd[0][0] == '\0') 
    { 
        cmd_not_found(NULL); 
        free_split(cmd); 
        _exit(127); 
    }

    if (ft_strchr(cmd[0], '/')) 
    {
        execve(cmd[0], cmd, envp);
        // ENOENT -> 127, прочие (EACCES/ENOEXEC/EPERM/...) -> 126
        int e = errno; perror("execve");
        free_split(cmd);
        _exit(e == ENOENT ? 127 : 126);
    }

    char *path = find_path(cmd[0], envp);
    if (!path) 
    {
        cmd_not_found(cmd[0]); 
        free_split(cmd); 
        _exit(127); 
    }

    execve(path, cmd, envp);
    int e = errno; perror("execve");
    free(path); free_split(cmd);
    _exit(e == ENOENT ? 127 : 126);
}
