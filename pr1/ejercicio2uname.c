#include <sys/utsname.h>
#include <errno.h>
#include <stdio.h>


int main(int argc,char **argv){

	struct utsname buffer;

	if(uname(&buffer) !=0){
		perror("Error en uname");
		return -1;
	}

   printf("nombre del sistema = %s\n", buffer.sysname);
   printf("nombre del nodo   = %s\n", buffer.nodename);
   printf("release     = %s\n", buffer.release);
   printf("version     = %s\n", buffer.version);
   printf("machine     = %s\n", buffer.machine);


}
