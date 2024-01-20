#include "../include/check_2_n_power.h"

int check_2_n_power(int length){

    int flag=0;

        while ( length > 1) {
            if ( length%2 ==1 ) flag++;
                length>>=1;
        }

   return flag;

}
