#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>

int hijos[50];
int contador = 0;
pid_t pid;

void handler(int senhal);

int main() {
	signal(SIGUSR1, handler); // si se recibe alguna de estas señales, llamar al
	signal(SIGUSR2, handler); // handler para que decida qué hacer.
	signal(SIGTERM, handler);
	signal(SIGINT, handler);

	printf("Para usar, ingresar en otra terminal: kill -s <USR1, USR2, TERM> %d\n", getpid());
	printf("SIGUSR1 => crear hijo e indicar la cant. total\n");
	printf("SIGUSR2 => eliminar hijo más antiguo e indicar la cant. total\n");

	while (1) {  // el programa "duerme" a la espera de que se le envíe
		sleep(1);  // una señal desde otro proceso.
	}
}

void handler(int senhal) {
	switch(senhal) {
		case SIGUSR1:
			pid = fork();
			if (pid == 0) {
				wait();  // crea el proceso hijo y lo suspende
			}
			else {
				hijos[contador] = pid;  // almacena el PID del hijo recien creado en el arreglo
				contador++;
				printf("Señal SIGUSR1 capturada. Hijo con PID %d creado.\n", pid);
				printf("La cant. actual de hijos es %d. \n", contador);
			}
			break;

		case SIGUSR2:
			printf("Señal SIGUSR2 capturada. ");
			if (contador > 0) {
				printf("Se procede a eliminar el hijo más viejo con PID %d.\n", hijos[0]);
				kill(hijos[0], SIGKILL -9);
				for (int i = 0; i < contador; i++) {
					hijos[i]=hijos[i++];
				}
				contador--;
				printf("La cant. actual de hijos es %d.\n", contador);
			}
			else {
				printf("No hay hijos que eliminar.\n");
			}
			break; 

		case SIGTERM:
			printf("Señal SIGTERM capturada. Procediendo a eliminar todos los hijos...\n");
			for (int i = 0; i < sizeof(hijos); i++) {
				kill(hijos[i], SIGKILL -9);
			}
			printf("Eliminación finalizada. Terminando programa...");
			exit(0);			
		
		case SIGINT:
			perror("Este programa no puede cerrarse con Ctrl-C!");
			break;
		}
}
