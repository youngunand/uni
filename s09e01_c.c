#include <stdlib.h>
#include <inttypes.h>


struct my_struct1 {
       float a[4];
       char b[8];
       double c;
   };

   struct my_struct2 {
       int32_t a;
       double b;
       float c;
   };

   struct my_struct3 {
       int32_t a;
       struct my_struct4 {
           int64_t x;
           uint16_t y;
       };
       struct my_struct2 b;
   };

   int main(void) {
    printf("size of my_struct1: %lu\n", sizeof(struct my_struct1));
    printf("size of my_struct2: %lu\n", sizeof(struct my_struct2));
    printf("size of my_struct3: %lu\n", sizeof(struct my_struct3));
    return EXIT_SUCCESS;
}