//SCHED_BATCH & SCHED_IDLE no estan definidos en el estandar posix
#define _GNU_SOURCE

#include <sched.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv){


	int schedv;
	if(argc !=2){
		printf("%s Usage <PID>",argv[0]);
		exit(EXIT_FAILURE);
	}
	int pid;
	struct sched_param param;
	sscanf(argv[1],"%d",&pid);
	if((schedv = sched_getscheduler(pid)) == -1){
		perror("sched_getscheduler");
		exit(EXIT_FAILURE);
	}

	if(sched_getparam(pid,&param) == -1){
		perror("sched_getparam");
		exit(EXIT_FAILURE);
	}


	printf("pid %s's current scheduling policy: ",argv[1]);
	switch(schedv){
	
		case SCHED_BATCH: printf("SCHED_BATCH\n"); break;
		case SCHED_OTHER: printf("SCHED_OTHER\n"); break;
		case SCHED_IDLE:  printf("SCHED_IDLE\n"); break;
		case SCHED_FIFO: printf("SCHED_FIFO\n"); break;
		case SCHED_RR: printf("SCHED_RR\n"); break;
		default: printf("UNKNOWN\n");break;
	}

	printf("pid %s's current scheduling priority: %i\n",argv[1],param.sched_priority);
	printf("Min priority: %i              max priority: %i\n",sched_get_priority_max(schedv),sched_get_priority_min(schedv));







}
