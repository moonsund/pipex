void    child_process(char *cmdline, char **envp)
{
    pid_t pid;
    int   fd[2];

    if (pipe(fd) == -1)
        error(); // желательно печатать perror и exit(EXIT_FAILURE)

    pid = fork();
    if (pid == -1)
        error();

    if (pid == 0) {
        // child: stdout -> pipe[1]
        if (dup2(fd[1], STDOUT_FILENO) == -1)
            error();                 // в дочернем лучше exit(127)
        close(fd[0]);
        close(fd[1]);                // после dup2 копия не нужна
        execute(cmdline, envp);      // внутри: execve(...) и при ошибке _exit(127)
        _exit(127);                  // на всякий случай, если execute не завершила
    } else {
        // parent: stdin <- pipe[0] для следующей стадии
        if (dup2(fd[0], STDIN_FILENO) == -1)
            error();
        close(fd[1]);
        close(fd[0]);
        // ВАЖНО: не ждём здесь! Копите pids и ждите позже.
        // waitpid(pid, NULL, 0);  // убрать отсюда
    }
}

void    here_doc(char *limiter, int argc)
{
    pid_t reader;
    int   fd[2];
    char *line;

    if (argc < 6)
        usage();
    if (pipe(fd) == -1)
        error();

    reader = fork();
    if (reader == -1)
        error();

    if (reader == 0) {
        // writer: пишет в pipe до limiter
        close(fd[0]);
        while (get_next_line(&line)) 
        {
            // уберём \n в конце (если есть) для точного сравнения
            size_t len = ft_strlen(line);
            if (len && line[len - 1] == '\n')
                line[len - 1] = '\0';
            if (ft_strcmp(line, limiter) == 0) {
                free(line);
                _exit(EXIT_SUCCESS);
            }
            // вернём \n если нужно или пишем как есть из gnl-версии
            write(fd[1], line, len);
            write(fd[1], "\n", 1); // если вырезали \n выше
            free(line);
        }
        _exit(EXIT_SUCCESS);
    } else 
    {
        // parent: читает из pipe как stdin для первой команды
        close(fd[1]);
        if (dup2(fd[0], STDIN_FILENO) == -1)
            error();
        close(fd[0]);
        // здесь подождать дочернего можно — это интерактивный ввод,
        // буфер не переполнится, но тоже не обязательно.
        waitpid(reader, NULL, 0);
    }
}

int main(int argc, char **argv, char **envp)
{
    int   i;
    int   filein;
    int   fileout;

    if (argc < 5)
        usage(); // и exit(1) внутри

    // Для ожидания всех промежуточных детей (если решите копить pids)
    // pid_t pids[argc - 3]; int pcount = 0;

    if (ft_strncmp(argv[1], "here_doc", 9) == 0) 
    {
        i = 3;
        fileout = open_file(argv[argc - 1], 0); // O_APPEND внутри
        here_doc(argv[2], argc);
    } else 
    {
        i = 2;
        fileout = open_file(argv[argc - 1], 1); // O_TRUNC внутри
        filein  = open_file(argv[1], 2);        // O_RDONLY внутри
        if (dup2(filein, STDIN_FILENO) == -1)
            error();
        close(filein);
    }

    // Запускаем все промежуточные команды без ожидания здесь
    while (i < argc - 2) {
        child_process(argv[i++], envp);
        // pids[pcount++] = last_pid; // если решите возвращать pid из child_process
    }

    // Последняя команда пишет сразу в fileout
    if (dup2(fileout, STDOUT_FILENO) == -1)
        error();
    close(fileout);

    // Теперь можно при желании дождаться всех, если вы их копили
    // for (int k = 0; k < pcount; ++k) waitpid(pids[k], NULL, 0);

    execute(argv[argc - 2], envp);
    // Если сюда дошли — exec не удался
    error(); // в дочернем было бы _exit(127), в main — exit(EXIT_FAILURE)
    return 1;
}
