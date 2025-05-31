#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdint.h>

#define PORT 9999

unsigned char global [1024];

void print_canary_32()
{
	uintptr_t v ;
	__asm__("mov %%gs :0x14,%0" : "=r" (v)) ;
	printf ("	server canary: %#lx\n", ( unsigned long ) v ) ;
}

void print_msg( unsigned char * msg , int len, size_t i  ){
	printf( "Recibido %d bytes : " , len ) ;
	for (i ; i < len ; i ++) {
		printf ( " %02x " , msg [ i ]) ;
	}
	printf ( "\n" ) ;
}

void vulnerable ( unsigned char * msg , int len ) {
	char buf [64];
	memcpy(buf, msg, len);
	//print_msg(msg, len, 64);
}

void handle ( int client ) {
	ssize_t r = read( client , global , sizeof(global) ) ;
	vulnerable(global,r) ;
	write(client,global,r) ;
	close(client) ;
	puts( " Conexión cerrada. " ) ;
	print_msg(global, r, 64);
}

int main ( void ) {
	int s = socket(AF_INET,SOCK_STREAM,0) ;
	struct sockaddr_in addr = {.sin_family = AF_INET ,
				   .sin_port = htons ( PORT ) ,
				   .sin_addr.s_addr = INADDR_ANY };
	bind(s , ( struct sockaddr *) & addr , sizeof(addr) ) ;
	listen(s , 1) ;

	printf ( " ==== Echo Server in port %d ==== \n" , PORT ) ;
	print_canary_32();
	while (1) {
		int c = accept (s , NULL , NULL ) ;
		if (! fork() ) {
			// proceso hijo
			close(s) ;
			handle(c) ;
			_exit(0) ;
		}
		close(c) ;
		// padre
	}
}
