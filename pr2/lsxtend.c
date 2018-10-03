#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>

//fonts color
#define FBLACK      "\033[30;"
#define FRED        "\033[31;"
#define FGREEN      "\033[32;"
#define FYELLOW     "\033[33;"
#define FBLUE       "\033[34;"
#define FPURPLE     "\033[35;"
#define D_FGREEN    "\033[6;"
#define FWHITE      "\033[7;"
#define FCYAN       "\x1b[36m"

////background color
#define BBLACK      "40m"
#define BRED        "41m"
#define BGREEN      "42m"
#define BYELLOW     "43m"
#define BBLUE       "44m"
#define BPURPLE     "45m"
#define D_BGREEN    "46m"
#define BWHITE      "47m"

////end color
#define NONE        "\033[0m"

/* El programa tiene un único argumento que es la ruta a un directorio.
 * Lista el directorio pasado por argumento 
 * */
int main(int argc, char **argv){

	DIR* dirp;
	struct dirent* direntp;
	char *linkname;
	struct stat sb;
	ssize_t r, bufsiz;
	int size;

	//Comprueba si se le ha pasado argumento
	if (argc != 2) {
		printf("Usage: %s <pathname>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	dirp = opendir(argv[1]);
	//si el puntero dirp es null significa que o no es un directorio o ha ocurrido un error al abrirlo
	if( dirp == NULL ) {
		printf("Can't open directory %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	direntp = readdir(dirp);
	/*Leemos la información contenida en la estructura direntp de la siguiente manera:
	 * Si el tipo es directorio se imprime el nombre del directorio seguido de "/"
	 * Si el tipo es enlace simbolico se imprime de la siguiente manera "nombre enlace"->"donde apunta"
	 * Si es un fichero regular simplemente se imprime su nombre por pantalla*/
	while(direntp != NULL){
		switch(direntp->d_type){
			case DT_DIR: printf(FWHITE BBLACK"%s/\n" NONE ,direntp->d_name);
				     break;
			case DT_LNK: if (lstat(direntp->d_name, &sb) == -1) {
					     perror("lstat");
					     exit(EXIT_FAILURE);
				     }
				     bufsiz = sb.st_size + 1;
				     /* Some magic symlinks under (for example) /proc and /sys
				      * report 'st_size' as zero. In that case, take PATH_MAX as
				      * a "good enough" estimate */
				     if (sb.st_size == 0)
					     bufsiz = PATH_MAX;
				     linkname = malloc(bufsiz);
				     if (linkname == NULL) {
					     perror("malloc");
					     exit(EXIT_FAILURE);
				     }

				     r = readlink(direntp->d_name, linkname, bufsiz);
				     if (r == -1) {
					     perror("readlink");
					     exit(EXIT_FAILURE);
				     }
				     linkname[r] = '\0';
				     printf(FPURPLE BBLACK"%s->%s\n" NONE ,direntp->d_name,linkname);
				     if (r == bufsiz)
					     printf("(Returned buffer may have been truncated)\n");
				     free(linkname);
				     break;
			case DT_REG: if(stat(direntp->d_name, &sb) == -1){
					     perror("stat");
					     exit(EXIT_FAILURE);
				     }
				     if(((sb.st_mode & S_IRWXU & S_IXUSR) == S_IXUSR) || ((sb.st_mode & S_IRWXG & S_IXGRP) == S_IXGRP) || ((sb.st_mode & S_IRWXO & S_IXOTH) == S_IXOTH)){
					     printf(FGREEN BBLACK"%s*\n"NONE,direntp->d_name);
				     }
				     printf("%s\n",direntp->d_name);

				     break;
			default: 
				     printf("Unknown\n");
				     break;
		}
		size = size + direntp->d_reclen;
		direntp = readdir(dirp);
	}
	printf(FRED BBLACK"\nTotal length: %i KBytes\n"NONE,size/1024);
	closedir(dirp);
	return EXIT_SUCCESS;
}
