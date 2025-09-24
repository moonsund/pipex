#include "pipex.h"

static char **parse_envp(char *const envp[]);

char	*find_path(char *cmd, char *const envp[])
{
    int i;
    char **paths;

    i = 0;
    paths = parse_envp(envp);
    while (paths[i])
    {
        char *path = ft_strjoin(paths[i], "/");
        if (!path) 
        {
            free_split(paths);
            return NULL;
        }
        char *path_join_cmd = ft_strjoin(path, cmd);
        free(path);
        if (path_join_cmd && access(path_join_cmd, X_OK) == 0)
        {
            free_split(paths);
            return (path_join_cmd);
        }
        free(path_join_cmd);
        i++;
    }
    free_split(paths);
    return (NULL);
}

static char **parse_envp(char *const envp[])
{
    int i;
    char **paths;

    i = 0;
    while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
        i++;
    if (!envp[i])
        return (NULL);
    paths = ft_split(envp[i] + 5, ':');
    if (!paths)
        return (NULL);
    i = 0;
    return (paths);
}

void sys_call_error(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

void cmd_exec_error(const char *msg)
{
    int e;
    
    e = errno;
    perror(msg);
    if (e == EACCES || e == ENOEXEC || e == EISDIR)
        exit(126);
    else if (e == ENOENT || e == ENOTDIR)
        exit(127);
    else
        exit(1);
}

void free_split(char **array)
{
    int i;

    i = 0;
    if (!array) 
        return;
    while (array[i])
    {
        free(array[i]);
        i++;
    }
    free(array);
}