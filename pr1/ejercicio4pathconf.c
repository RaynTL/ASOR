#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int main(int argc, char **argv){

	printf("Nombre de fichero en /home/: %ld\n", pathconf("/home/",_PC_NAME_MAX));
	printf("Tamaño maximo de la ruta en /home/: %ld\n", pathconf("/home/",_PC_PATH_MAX));
	printf("Numero maximo de enlaces en /home/: %ld\n", pathconf("/home/",_PC_LINK_MAX));

}
