#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>



int main (int argc, char **argv){

	pid_t mipid,pid,w;
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
			if(execvp(argv[1],argv+1) == -1){
				perror("execvp error");
				exit(EXIT_FAILURE);
			}
		default:

			do{
				w = waitpid(pid,&wstatus,WUNTRACED | WCONTINUED);
				if(w == -1){
					perror("waitpid");
					exit(EXIT_FAILURE);
				}

				if (WIFEXITED(wstatus)) {
					printf("exited, status=%d\n", WEXITSTATUS(wstatus));
				}

			}while(!WIFEXITED(wstatus));
	
		break;
		
	}

}
