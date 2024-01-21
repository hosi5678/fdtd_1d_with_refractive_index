#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../include/common_parameter.h"
#include "../include/get_dt.h"

double get_dt(void){

   if(dimension==1){
      return dx/light_speed;
   }else{
      if(time_margin==1.0){
         printf("error. time_margin<1.0\n");
         exit(1);
      }

      return dx*time_margin/(sqrt(dimension)*light_speed);

   }

}
