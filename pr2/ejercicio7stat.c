#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/sysmacros.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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

	printf("Major: %ld | Minor: %ld\n",(long) major(buf.st_dev),(long) minor(buf.st_dev));
	printf("Inode number: %ld\n", (long) buf.st_ino);
	printf("File type:     ");
	switch (buf.st_mode & S_IFMT) {
	           case S_IFBLK:  printf("block device\n");            break;
	           case S_IFCHR:  printf("character device\n");        break;
	           case S_IFDIR:  printf("directory\n");               break;
	           case S_IFIFO:  printf("FIFO/pipe\n");               break;
	           case S_IFLNK:  printf("symlink\n");                 break;
	           case S_IFREG:  printf("regular file\n");            break;
	           case S_IFSOCK: printf("socket\n");                  break;
	           default:       printf("unknown?\n");                break;
	}
	printf("Last status change:       %s", ctime(&buf.st_ctime));

}
