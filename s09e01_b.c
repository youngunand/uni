#include <stdio.h>
#include <stdlib.h>

struct my_struct1 {
    float x;
    double y;
};

struct my_struct2 {
    float x;
    float y;
    double z;
};

struct my_struct3 {
    float x;
    double y;
    float z;
};

int main(void) {
    printf("size of my_struct1: %lu\n", sizeof(struct my_struct1));
    printf("size of my_struct2: %lu\n", sizeof(struct my_struct2));
    printf("size of my_struct3: %lu\n", sizeof(struct my_struct3));
    return EXIT_SUCCESS;
}