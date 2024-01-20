#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/common_parameter.h"
#include "../include/checkAlloc1DDouble.h"

int *checkAlloc1DInt(const char *str_msg,int length){

    int char_s_length;
    char_s_length=strlen(str_msg);

    char *s_msg=(char *)calloc( char_s_length + 1 , sizeof(char) );

    static int *vec;

    strcpy(s_msg,str_msg);

    vec=(int *)calloc(length,sizeof(int));

    if(NULL==vec){
        printf("(in %s)\n",s_msg);
        printf("calloc error. exit...\n");
        exit(1);
    }

    return vec;

}
