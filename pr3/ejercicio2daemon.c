#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

int main (int argc, char **argv){

	pid_t pid, sid;
	int wstatus;

	if(argc < 2){
		printf("Usage: %s <command>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	pid = fork();


	switch(pid){


		case -1:
			perror("fork");
			exit(EXIT_FAILURE);
		case 0:
			sid = setsid();
			if(sid == -1){
				perror("setsid error");
				exit(EXIT_FAILURE);
			}
			int w;
			w = chdir("/tmp");
			if(w == -1){
				perror("chdir error");
				exit(EXIT_FAILURE);
			}
			int fileok,fileerr,entrada;
			fileok = open("daemon.out",O_CREAT | O_APPEND | O_WRONLY | O_TRUNC,0666);
			fileerr = open("daemon.err",O_CREAT | O_APPEND | O_WRONLY | O_TRUNC,0666);
			entrada = open("/dev/null",O_WRONLY);
			if(fileok == -1 || fileerr == -1){
				perror("open error");
				exit(EXIT_FAILURE);
			
			}
			dup2(fileok,1);
			dup2(fileerr,2);
			dup2(entrada,0);

			close(fileok);
			close(fileerr);
			close(entrada);

			if(execvp(argv[1],argv+1)== -1){
				perror("execvp error");
				exit(EXIT_FAILURE);
			}

			break;
		
		default:

			printf("process_id of child process %d \n", pid);
			// return success in exit status
			exit(EXIT_SUCCESS);
			break;
		
	}

}
