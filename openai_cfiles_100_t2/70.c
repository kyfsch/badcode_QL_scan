#include <stdio.h>

char* retrieveString(char* gstr) {
    return gstr;
}


To use this function, simply pass the `gstr` variable as an argument and assign the return value to a variable of type `char*`:

c
char* myString = retrieveString(gstr);
