#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#ifndef DNI 
 #error de compilacion , denife el DNI 
#endif 
#define BUFSIZE (64 + ( DNI % 23) ) 

void vulnerable () { 
	char buffer [BUFSIZE];	
	printf ( "Introduce datos: ");
	gets (buffer); 
	printf ( "Has introducido: %s \n" , buffer); 
}

int main () { 
	vulnerable (); 
	printf ("Exploit failied \n");
       	return 0;
}

