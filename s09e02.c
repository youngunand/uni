#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

void reverse(char bits[], size_t length) {
    for (size_t i = 0; i < length/2; i++) {
        char temp = bits[i];
        bits[i] = bits[length-1-i];
        bits[length-1-i] = temp;
    }
}

void get_binary_represantation (double user_input, char bits []) {
    union {
        double value;
        uint64_t u;
    } double_union;
    
    double_union.value = user_input;

    uint64_t var_helper = double_union.u;
    
    for (size_t i = 0; i < 66; i++)
    {
        if(i == 64 || i == 52) { // insert empty spaces (52 and 64 because list gets reversed afterwards)
            bits[i] = ' ';
            continue;
        }
        if(var_helper%2==0) {
            bits[i] = '0';
        } else {
            bits[i] = '1';
        }
        var_helper = var_helper/2;
    }
    
    reverse(bits, 66);
}


int main(int argc, char const *argv[])
{


    if(argv[1] == NULL) {
        fprintf(stderr, "usage: ./s09e02 <double>");
        return EXIT_FAILURE;
    }

    //use argc because of flags
    double user_input = argc;
    char *end_ptr;
    user_input = strtod(argv[1], &end_ptr);

    if(*end_ptr != '\0') {
        fprintf(stderr,"ERROR: %s is not a valid double!\n", argv[1]);
        fprintf(stderr,"Extracted double component: %f\n",user_input);
        fprintf(stderr,"Remaining: %s\n", end_ptr);
        return EXIT_FAILURE;
    }

    printf("Number: %e\nBinary representation:\n   ", user_input);

    char bits [65]; //66 characters because of two empty spaces
    get_binary_represantation(user_input, bits);
    
    //there were errors in artemis with //printf("%s\n", bits);
    for (size_t i = 0; i < 66; i++)
    {
        printf("%c", bits[i]);
    }
    printf("\n");
    
    //empty spaces as described in exercise (can be done differently?)
    printf("sign    exponent                                             mantissa\n");
    
    return EXIT_SUCCESS;
}