 #include <sys/types.h>
 #include <pwd.h>
 #include <unistd.h>
 #include <stdio.h>
 
int main()
{
	  uid_t uid;
          uid_t euid;
	  struct passwd *user;
	  uid = getuid();
	  euid = geteuid();
          printf("UID: %u\n", uid);
	  printf("EUID: %u\n", euid);
	  if((user = getpwuid(uid)) == NULL){
	  
	  	perror("error getpwnam:");
	  }
	  else{
	   
	  	printf("Nombre de usuario: %s\n", user->pw_name);
	  	printf("Directorio Home: %s\n", user->pw_dir);
		printf("Informacion de usuario: %s\n", user->pw_gecos);
	  }
	  
}
