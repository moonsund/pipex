#include <unistd.h>
#include <stdio.h>

int main(void)
{
    int fd[2];
    char buffer[20];

    if (pipe(fd) == -1)
    {
        perror("pipe");
        return 1;
    }

    if (fork() == 0) // дочерний процесс
    {
        close(fd[1]); // закрываем запись
        ssize_t n = read(fd[0], buffer, sizeof(buffer) - 1);
        if (n > 0)
        {
            buffer[n] = '\0'; // обязательно закрываем строку
            printf("Child read: %s\n", buffer);
        }
    }
    else // родительский процесс
    {
        close(fd[0]); // закрываем чтение
        write(fd[1], "Hello pipe!", 11); // 11 символов + '\0' не пишем специально
    }

    return 0;
}
