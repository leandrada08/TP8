#include "reloj.h"
#include <stdio.h>

#define TAMANIO_VECTOR_TIEMPO 6
// Defino las estructuras
struct clk_s{
    uint8_t hora_actual[TAMANIO_VECTOR_TIEMPO];
    uint8_t tics;
    uint8_t tics_por_segundo;
    bool hora_valida;

    uint8_t alarma[TAMANIO_VECTOR_TIEMPO];
    bool alarma_valida;

    uint8_t posponer[TAMANIO_VECTOR_TIEMPO];
    bool posponer_valida;

    suena_alarma_t gestor_alarma;
};


// Defino las variables globales
static struct clk_s instances;

// Declaracion de funciones privadas
void VerificarAlarma(clk_t reloj);


// Definicion de funciones privadas


void VerificarAlarma(clk_t reloj){
    if(reloj->hora_valida!=0 && reloj->alarma_valida!=0){
        if(memcmp(reloj->hora_actual,reloj->alarma, TAMANIO_VECTOR_TIEMPO)==0){
            reloj->gestor_alarma(reloj);
            if(reloj->posponer_valida==1){
                reloj->posponer_valida=0;
                memcpy(reloj->alarma ,reloj->posponer, TAMANIO_VECTOR_TIEMPO);
            }
        }
    }
}


// Defino las funciones publicas
clk_t ClkCreate(int tics_por_segundo, suena_alarma_t gestor_alarma){
    memset(&instances, 0, sizeof(instances));
    instances.tics_por_segundo=tics_por_segundo;
    instances.gestor_alarma=gestor_alarma;
    return &instances;
}

bool ClkGetTime(clk_t reloj, uint8_t * hora, int size){
    memcpy(hora ,reloj->hora_actual, size);
    return reloj->hora_valida;
}


void ClkSetTime(clk_t reloj, const uint8_t * hora, int size){
    memcpy(reloj->hora_actual, hora, size);
    reloj->hora_valida = true;
}


/** @brief
 *
 *
*/
void ClkTick(clk_t reloj){
    reloj->tics++;
    if(reloj->tics==reloj->tics_por_segundo){
        reloj->hora_actual[5]++;
        reloj->tics=0;
    }
    if(reloj->hora_actual[5]==10){
        reloj->hora_actual[5]=0;
        reloj->hora_actual[4]++;
    }
    if(reloj->hora_actual[4]==6){
        reloj->hora_actual[4]=0;
        reloj->hora_actual[3]++;
        VerificarAlarma(reloj);
    }
    if(reloj->hora_actual[3]==10){
        reloj->hora_actual[3]=0;
        reloj->hora_actual[2]++;
        VerificarAlarma(reloj);
    }
    if(reloj->hora_actual[2]==6){
        reloj->hora_actual[2]=0;
        reloj->hora_actual[1]++;
        VerificarAlarma(reloj);
    }
    if(reloj->hora_actual[1]==10){
        reloj->hora_actual[1]=0;
        reloj->hora_actual[0]++;
        VerificarAlarma(reloj);
    }
    if(reloj->hora_actual[0]==2 && reloj->hora_actual[1]==4){
        reloj->hora_actual[0]=0;
        reloj->hora_actual[1]=0;
        VerificarAlarma(reloj);  
    }
    


}


bool ClkGetAlarma(clk_t reloj,uint8_t * hora, int size){
    memcpy(hora ,reloj->alarma, size);
    return reloj->alarma_valida;
}




void ClkSetAlarma(clk_t reloj,const uint8_t * hora, int size){
    memcpy(reloj->alarma, hora, size);
    reloj->alarma_valida = true;
}


void ClkActivateAlarma(clk_t reloj,bool estado){
    if(estado==0){
        reloj->alarma_valida = false;
    }
    if(estado==1){
        reloj->alarma_valida = true;
    }
}


void PosponerAlarma(clk_t reloj,uint8_t posponer, bool estado){
    if(estado){
        memcpy(reloj->posponer ,reloj->alarma, TAMANIO_VECTOR_TIEMPO);
        reloj->posponer_valida=1;
        ApagarAlarma(reloj);
        for(int i=0; i<posponer;i++){
            reloj->alarma[3]++;
            if(reloj->alarma[3]==10){
                reloj->alarma[3]=0;
                reloj->alarma[2]++;

            }
            if(reloj->alarma[2]==6){
                reloj->alarma[2]=0;
                reloj->alarma[1]++;

            }
            if(reloj->alarma[1]==10){
                reloj->alarma[1]=0;
                reloj->alarma[0]++;

            }
            if(reloj->alarma[0]==2 && reloj->alarma[1]==4){
                reloj->alarma[0]=0;
                reloj->alarma[1]=0;
        
            }
        }
    }
}


void ApagarAlarma(clk_t reloj){
    reloj->gestor_alarma(reloj);
}
