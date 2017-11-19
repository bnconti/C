#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void imprimir_pid(int i) {  // para ir verificando si los procesos se crean correctamente
	printf("\ni = %i\n", i);
	printf("PID = %i\n", getpid());
	printf("PPID = %i\n", getppid());
}

int main(){
	pid_t hijo, hijo_2, hijo_3;
	printf("PPID original: %i\n", getpid());
	for (int i = 1; i<4; i++) {
		if (i != 2) {  // si no es el 2do caso (donde tiene que crear más de un hijo)...
			hijo = fork();
			if (hijo == 0) {  // si es el proceso hijo...
				imprimir_pid(i);
				exit(0);  // exit para finalizar hijo
			} else if (hijo != 0) {
				wait(hijo);  // espera al hijo para que no se desorganise todo
			}
		} else {
			hijo = fork();
			if (hijo == 0) {
				imprimir_pid(i);
				hijo_2 = fork();
				if (hijo_2 == 0) {
					imprimir_pid(i);
					hijo_3 = fork();
					if (hijo_3 == 0) {
						imprimir_pid(i);
						exit(0);  // exit para finalizar hijo_3
					} else if (hijo_3 != 0) {
						wait(hijo_3);
					}
					exit(0);  // exit para finalizar hijo_2
				} else if (hijo_2 != 0) {
					wait(hijo_2);
				}
				exit(0);  // exit para finalizar hijo
			} else if (hijo != 0) {
				wait(hijo);
			}
		}
	}
}
