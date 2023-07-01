#include "bcd.h"


void IncrementarBCD(uint8_t numero[2],const uint8_t limite[2]){
    numero[1]++;
    if(numero[1]==10){
        numero[1]=0;
        numero[0]++;
    }
    if(numero[0]==limite[0] && numero[1]==limite[1]){
        numero[0]=0;
        numero[1]=0;
    }
}


void DecrementarBCD(uint8_t numero[2],const uint8_t limite[2]){
    numero[1]--;
    if(numero[1]==-1){
        if(numero[0]==0){
            numero[0]=limite[0];
            numero[1]=limite[1];
        }else{
            numero[1]=9;
            numero[0]--;
        }
    }
}
