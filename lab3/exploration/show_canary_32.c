#include <stdio.h>
#include <stdint.h>

/*
Con ssp:

0x9037ab00
0xfd56f600
0xabd8c00
0x1ddd3400
0xd4d76300

Sin ssp:

0xc26e5600
0x9d9a9100
0xeccaf000
0x38a23f00
0x8a470300
*/

static inline uintptr_t stack_cookie ( void )
{
	uintptr_t v ;
	__asm__("mov %%gs :0x14,%0" : "=r" (v)) ;
	return v ;
}


int main ( void )
{
	printf ("%#lx\n", ( unsigned long ) stack_cookie() ) ;
	return 0;
}
