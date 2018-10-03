#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char **argv){

	
	if(argc != 2){
		printf("Usage: %s <pathname>\n",argv[0]);
		exit(EXIT_FAILURE);
	}
	int file;
	file = open(argv[1],O_CREAT | O_APPEND | O_WRONLY,0777);

	if(file == -1){
		perror("Error open");
		exit(EXIT_FAILURE);
	}
	dup2(file,1);
	printf("prueba de salida estandar\n");
	close(file);
}
