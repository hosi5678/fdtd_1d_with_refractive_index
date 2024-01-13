#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../common_include/checkAlloc1DDouble.h"

double *checkAlloc1DDouble(const char *str_msg,int length){

    int char_s_length;
    char_s_length=strlen(str_msg);

    char *s_msg=(char *)calloc(char_s_length+1,sizeof(char));

    strcpy(s_msg,str_msg);

    static double *vec;

    vec=(double *)calloc(length,sizeof(double));

    if(NULL==vec){
        printf("%s\n",s_msg);
        perror("calloc error. exit...\n");
        exit(1);
    }

    free(s_msg);

    return vec;

}
