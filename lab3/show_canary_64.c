#include <stdio.h>
#include <stdint.h>

/*
0xf55e03beef3d6000
0x7078a888480e8700
0xc243a772ad951100
0x3c80aa0c4f2ea00
0xbbcd075a28ba3200
*/

static inline uintptr_t stack_cookie ( void )
{
	uintptr_t v ;
	__asm__("mov %%fs :0x28,%0" : "=r" (v)) ;
	return v ;
}


int main ( void )
{
	printf ("%#lx\n", ( unsigned long ) stack_cookie() ) ;
	return 0;
}
