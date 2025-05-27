#include <stdio.h>
#include <stdlib.h>

int main () {
	int x = 10;
	int *px = &x;
	printf("x=%d\n",x);
	printf("Direccion de x: %p \n", (void*)&x);
	printf("px = %p\n", (void*) px);
	printf("px = %d\n", *px);
	return 0;

}
