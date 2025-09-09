#include <unistd.h>
#include <stdio.h>

int main(void)
{
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork error");
    }
    else if (pid == 0) {
        // Это ребёнок
        printf("Child process:\n");
        printf("  getpid()  = %d (мой PID)\n", getpid());
        printf("  getppid() = %d (PID моего родителя)\n", getppid());
    }
    else {
        // Это родитель
        printf("Parent process:\n");
        printf("  getpid()  = %d (мой PID)\n", getpid());
        printf("  fork()    = %d (PID ребёнка, возвращённый fork)\n", pid);
        printf("  getppid() = %d (PID моего родителя — например, bash)\n", getppid());
    }

    return 0;
}
