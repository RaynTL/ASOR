#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char **argv){

	if(argc !=2){
		printf("Usage: %s <pathname>\n",argv[0]);
		exit(EXIT_FAILURE);
	}
	struct flock fl,sfl;
	int fd = open(argv[1],O_RDWR);
	if(fd == -1){
		printf("Error abrir fichero %s", argv[1]);
		exit(EXIT_FAILURE);
	}
	fl.l_type  = F_WRLCK;  
	fl.l_start   = 0;
	fl.l_whence  = SEEK_SET;
	fl.l_len     = 0;   
	sfl = fl;
	if (fcntl(fd, F_GETLK, &fl) == -1) {
		perror("fcntl error");
		exit(EXIT_FAILURE);
	}
	printf("Mi pid: %ld\n", getpid());
	switch(fl.l_type){
		case F_WRLCK:
			printf("Bloqueado escritura por proceso: %ld\n",fl.l_pid);
			break;
		case F_RDLCK:
			printf("Bloqueado lectura por proceso: %ld\n",fl.l_pid);
			break;
		default: 
			printf("No bloqueado, bloqueando de escritura durante 30 segundos...\n");
			fcntl(fd,F_SETLK,sfl);
			sleep(30);
			break;
	
	}
	close(fd);

}
