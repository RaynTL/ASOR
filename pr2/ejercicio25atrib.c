#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>



int main(){


	mode_t oldMask;
	oldMask = umask(027);
	if(open("./prueba",O_APPEND | O_CREAT | O_TRUNC) == -1){

		perror("Error open");
		umask(oldMask);
		return -1;
}
	else{
		umask(oldMask);
		return 0;

}


}
