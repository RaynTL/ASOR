#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>


int main (int argc, char **argv){

struct addrinfo hints,*result;
int s;
if(argc !=2){
	printf("Usage %s <domain>\n",argv[0]);
	exit(EXIT_FAILURE);
}

hints.ai_socktype = 0;

s = getaddrinfo(argv[1],NULL,&hints,&result);

if(s){
	fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
	exit(EXIT_FAILURE);
}
struct addrinfo *p;
char host[256];
for(p = result; p!=NULL;p = p->ai_next){
	
	 getnameinfo(p->ai_addr, p->ai_addrlen, host, sizeof(host), NULL, 0, NI_NUMERICHOST);
	 printf("%s     %i     %i\n",host,p->ai_family,p->ai_socktype);

}

}
