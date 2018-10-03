
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main (int argc, char **argv){

  int i;

    for (i = 0; i < sys_nerr; ++i){
	        fprintf(stdout, "%d : %s\n", i, strerror(i));


    }


}
