#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>

void print_usage(const char *prog) {
    fprintf(stderr, "Uso: %s -32|-64 <direccion1> <direccion2>\n", prog);
    fprintf(stderr, "Ejemplo: %s -32 f7fc8900 f7fd6400\n", prog);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        print_usage(argv[0]);
        return EXIT_FAILURE;
    }

    int bits = 0;
    if (strcmp(argv[1], "-32") == 0) {
        bits = 32;
    } else if (strcmp(argv[1], "-64") == 0) {
        bits = 64;
    } else {
        print_usage(argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    unsigned long long a1 = strtoull(argv[2], NULL, 16);
    if (errno != 0) {
        perror("Error convirtiendo direccion 1");
        return EXIT_FAILURE;
    }
    unsigned long long a2 = strtoull(argv[3], NULL, 16);
    if (errno != 0) {
        perror("Error convirtiendo direccion 2");
        return EXIT_FAILURE;
    }

    if (bits == 32) {
        if (a1 > UINT32_MAX || a2 > UINT32_MAX) {
            fprintf(stderr, "Error: una de las direcciones excede el rango de 32 bits\n");
            return EXIT_FAILURE;
        }
    }

    unsigned long long diff;
    if (a1 > a2) diff = a1 - a2;
    else diff = a2 - a1;

    printf("Distancia entre 0x%llx y 0x%llx: %llu (0x%llx)\n", a1, a2, diff, diff);
    return EXIT_SUCCESS;
}

