#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>

#define PORT 9999

#define DNI 2086546955761158
#define BUFSIZE (64 + ( DNI % 23) )  
 
void vulnerable(int client_fd, int client_id) {
    	char buffer [BUFSIZE];	
	printf ( "Se atiende al cliente #%d \n", client_id);
	read(client_fd, buffer, 300); 
	printf("Se recibe como payload: %s \n", buffer);
}
 
int main() {
    int sockfd, client_fd;
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t cli_len = sizeof(cli_addr);
 
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);
 
    bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
    listen(sockfd, 5);
    
    printf ( " ==== Server in port %d ==== \n" , PORT) ;
    int client_id = 0;
    
    while (1) {
        client_fd = accept(sockfd, (struct sockaddr *) &cli_addr, &cli_len);
    	client_id++;
        if (fork() == 0) {
            // Proceso hijo
            close(sockfd);
            vulnerable(client_fd, client_id);
            exit(0);
        } else {
            // Padre
            close(client_fd);
            wait(NULL);
        }
    }
 
    return 0;
}
