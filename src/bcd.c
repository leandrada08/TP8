
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
	if (numero[1] > 9) {
		numero[1] = 9;
		if (numero[0] > 0) numero[0]--;
		else {
            if(limite[0]==2){
                numero[0] = limite[0];
            }else{
                numero[0] = limite[0]-1;
            }
            if(limite[1]!=0){
                numero[1] = limite[1]-1;
            }else{
                numero[1] = 9;
            }
		}
	}
}
