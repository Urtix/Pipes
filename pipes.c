#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int pipe1[2], pipe2[2];
    pid_t pid;
    char msg[10];
    
    pipe(pipe1);  // A → B
    pipe(pipe2);  // B → A
    
    pid = fork();
    
    if (pid == 0) {
        // Процесс B
        close(pipe1[1]);
        close(pipe2[0]);
        
        while (1) {
            printf("\n");
            // Ожидание сигнала от A
            read(pipe1[0], msg, sizeof(msg));
            printf("B: SLEEP → READY (получил: %s)\n", msg);
            
            // Отправка сигнала
            write(pipe2[1], "pong", 5);
            printf("B: READY → SLEEP (отправил pong)\n");
        }
        
    } else {
        // Процесс A
        close(pipe1[0]);
        close(pipe2[1]);
        
        // Первый сигнал B
        write(pipe1[1], "ping", 5);
        printf("A: READY → SLEEP (отправил ping)\n");
        
        while (1) {
            printf("\n");
            // Ожидание ответа от B
            read(pipe2[0], msg, sizeof(msg));
            printf("A: SLEEP → READY (получил: %s)\n", msg);
            
            // Отправка сигнала
            write(pipe1[1], "ping", 5);
            printf("A: READY → SLEEP (отправил ping)\n");
        }
    }
    
    return 0;
}
