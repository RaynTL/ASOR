#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/sysmacros.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char **argv){

	struct stat buf;
	if (argc != 2) {
		printf("Usage: %s <pathname>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	if (stat(argv[1], &buf) == -1) {
		perror("stat");
		exit(EXIT_FAILURE);
	}

	switch (buf.st_mode & S_IFMT) {
		case S_IFREG:  
			printf("regular file: %s creating hard and symbolic links in directory\n",argv[1]); 
			link(argv[1],"./hardlink"); 
			symlink(argv[1],"./symlink");
			break;
		default:       printf("Not a regular file, cant create links\n");                break;
	}


}
