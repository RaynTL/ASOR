#include <time.h>
#include <locale.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <errno.h>

int main(){

time_t tiempo;
struct timeval tv; 
time(&tiempo);
char *tlegible;
char outstr[200];
tlegible = ctime(&tiempo);
printf("%s\n",tlegible);
int t1;
struct tm *timelocal;
setlocale(LC_ALL, "");


if(gettimeofday(&tv,NULL) == 0){
	printf("Antes del bucle: %i\n", tv.tv_usec);
	t1 = tv.tv_usec;
}
else{
	perror("Error en gettimeofday");
}
int var = 0;

while(var < 10000){

	var=var+1;

}

if(gettimeofday(&tv,NULL) == 0){
        printf("Despues del bucle: %i\n", tv.tv_usec);
        printf("restante: %i\n", tv.tv_usec-t1);
}
else{
        perror("Error en gettimeofday");
}

if((timelocal = localtime(&tiempo)) != NULL){

	printf("Estamos en el año %i\n", 1900 + timelocal->tm_year);
}

else{

	perror("Error timelocal");
} 


if(strftime(outstr,sizeof(outstr), "%A,%H:%M", timelocal) == 0){

	perror("Error strftime");

}

else{

	printf("Hoy es %s\n", outstr);

}

}
