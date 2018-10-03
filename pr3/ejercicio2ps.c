#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdlib.h>
#include <stdio.h>

int main (int argc, char **argv){

	struct rlimit limit;

	printf("PID: %i             PPID: %i\n",getpid(),getppid());
	printf("PGID: %i            SID: %i\n",getpgid(getpid()),getsid(getpid()));
	
	if(getrlimit(RLIMIT_NOFILE,&limit) == -1){
		perror("Error getrlimit");
		exit(EXIT_FAILURE);
	}
	printf("The max number of fd to be open by this process: %i\n",limit.rlim_max);

	exit(EXIT_SUCCESS);



}
