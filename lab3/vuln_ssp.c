#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

void vulnerable () { 
	char buffer [64];	
	printf ( "Introduce datos: ");
	gets (buffer); 
	printf ( "Has introducido: %s \n" , buffer); 
}

int main () { 
	vulnerable (); 
	printf ("Exploit failied \n");
       	return 0;
}

