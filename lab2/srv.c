#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>

#define PORT 9999 

unsigned char global [1024];
 
void vulnerable( unsigned char * msg , int len ) {
    	char buffer [64];	
	memcpy(buffer, msg, len);
}

void handle_client(int fd, int id){
    ssize_t r = read(fd , global , sizeof(global) ) ;
    printf ( "Se atiende al cliente #%d \n", id);
    vulnerable(global,r) ;
    close(fd) ;
    puts( " Conexión cerrada. " ) ;
}


int main() {
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in addr = {.sin_family = AF_INET ,
				   .sin_port = htons ( PORT ) ,
				   .sin_addr.s_addr = INADDR_ANY };
	bind(sockfd , ( struct sockaddr *) & addr , sizeof(addr) ) ;
	listen(sockfd , 1) ;

	printf ( " ==== Server in port %d ==== \n" , PORT) ;
	int client_id = 0;

	while (1) {
		int client_fd = accept(sockfd, NULL, NULL);
		client_id++;
		if ( !fork() ) {
		    // Proceso hijo
		    close(sockfd);
		    handle_client(client_fd, client_id);
		    exit(0);
		}
		close(client_fd) ;
		// padre
	}

	return 0;
}
