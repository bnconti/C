#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void imprimir_pid(int i) {  // para ir verificando si los procesos se crean correctamente
	printf("\ni = %i\n", i);
	printf("PID = %i\n", getpid());
	printf("PPID = %i\n", getppid());
}

int main() {
	pid_t hijo;
	printf("PPID original: %i\n", getpid());
	for (int i = 1; i<8; i++) {
		hijo = fork();
        if (hijo == 0) {
            imprimir_pid(i);
            exit(0);
        }
    }
}
    
