#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>


/*
 * uso:
 *
 *
 *            $ ./a.out &
 *             Child PID is 32360
 *             [1] 32359
 *            $ kill -STOP 32360
 *             stopped by signal 19
 *            $ kill -CONT 32360
 *             continued
 *            $ kill -TERM 32360
 *             killed by signal 15
 *            $
 */



int main(int argc, char **argv){

	pid_t mipid, pid,w;
	int wstatus;
	pid = fork();


	switch(pid){

		case -1: 
			perror("fork"); exit(EXIT_FAILURE);
			break;
		case 0: 
			mipid = getpid();
			printf("Proceso hijo %i (padre: %i)\n",mipid,getppid());
			pause(); // dejarlo en estado de pausa hasta que una señal lo mate o lo pare
			break;
		default:
			mipid = getpid();
			printf("Proceso padre %i (hijo %i)\n",mipid,pid);
			do{

				w = waitpid(pid,&wstatus,WUNTRACED | WCONTINUED); // nueva llamada mas detallada
				if (w == -1) {
					perror("waitpid");
					exit(EXIT_FAILURE);
				}

				if (WIFEXITED(wstatus)) {
					printf("exited, status=%d\n", WEXITSTATUS(wstatus));
				} else if (WIFSIGNALED(wstatus)) {
					printf("killed by signal %d\n", WTERMSIG(wstatus));
				} else if (WIFSTOPPED(wstatus)) {
					printf("stopped by signal %d\n", WSTOPSIG(wstatus));
				} else if (WIFCONTINUED(wstatus)) {
					printf("continued\n");
				}


			}while(!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus));
			exit(EXIT_SUCCESS);
	}


}
