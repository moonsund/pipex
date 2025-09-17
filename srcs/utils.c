#include "pipex.h"

char	*find_path(char *cmd, char *const envp[])
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
    while (paths[i])
    {
        char *path = ft_strjoin(paths[i], "/");
        if (!path)
            return (NULL);
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

void error(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

void error127(const char *msg)
{
    perror(msg);
    exit(127);
}

void exec_error_exit(const char *cmd)
{
    perror(cmd);
    if (errno == ENOENT) // команда/файл не найден
        exit(127);
    else if (errno == EACCES || errno == EPERM || errno == ENOEXEC)
        exit(126); // найдено, но не исполняемо/нет прав/не исполняемый формат
    else
        exit(EXIT_FAILURE); // прочая ошибка execve
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