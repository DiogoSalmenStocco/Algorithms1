#include <stdio.h>
#include <stdlib.h>
#include "String.h"

int main(int argc, char const *arcv[])
{
    String *str = createString("Oi como vai?");
    if (str == NULL)
    {
        printf("Opa erro\n");
        exit(0);
    }


    printf("%s\n", c_str(str));
    delString(str);
    return 0;
}