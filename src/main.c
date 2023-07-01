

#include "bsp.h"
#include "reloj.h"
#include "bcd.h"
#include <stdbool.h>
#include <stddef.h>

/* Definicion de macros*/
#ifndef TICS_POR_SEGUNDO
#define TICS_POR_SEGUNDO 1000
#endif

#ifndef PERIODO_PARPADEO
#define PERIODO_PARPADEO 200
#endif

#ifndef POSPONER_MINUTOS
#define POSPONER_MINUTOS 5
#endif



/* Delacacion de datos privados*/
typedef enum{
    SIN_CONFIGURAR,
    MOSTRANDO_HORA,
    AJUSTANDO_MINUTOS_ACTUAL,
    AJUSTANDO_HORAS_ACTUAL,
    AJUSTANDO_MINUTOS_ALARMA,
    AJUSTANDO_HORAS_ALARMA,
} modo_t;

/*Declaracion de funciones Privadas*/

/**
 * @brief Funcion para activar el buzzer de la alarma
 * 
 * @param reloj Reloj al cual le activaremos la alarma
 */
void ToggleAlarma(clk_t reloj);



/**
 * @brief Funcion para cambiar el estado en el que nos encontramos y actualizar la pantalla al correspondiente estado
 * 
 * @param valor modo en el que nos encontramos
 */
void CambiarModo(modo_t valor);

/*Definicion de variable publicas*/
static board_t board;

static clk_t reloj;

static modo_t modo;

static bool sonando_alarma = false;


/*Definicion de variables privada*/

static const uint8_t LIMITE_MINUTO[]={6,0};

static const uint8_t LIMITE_HORA[]={2,4};


/*Imprementacion de funciones publicas*/
void ToggleAlarma(clk_t reloj){
    if(sonando_alarma!=0){
        sonando_alarma=false;
        DigitalOutputDesactivate(board->buzzer);
    }else{
        sonando_alarma=true;
        DigitalOutputActivate(board->buzzer);
    }

}

void CambiarModo(modo_t valor){
    modo = valor;
    switch (modo)
    {
    case SIN_CONFIGURAR:
        DisplayFlashDigits(board->display,0,3,PERIODO_PARPADEO);
        break;
    case MOSTRANDO_HORA:
        DisplayFlashDigits(board->display, 0, 0, 0);
        break;
    case AJUSTANDO_MINUTOS_ACTUAL:
        DisplayFlashDigits(board->display, 0, 1, PERIODO_PARPADEO);
        break;
    case AJUSTANDO_HORAS_ACTUAL:
        DisplayFlashDigits(board->display, 2, 3, PERIODO_PARPADEO);
        break;
    case AJUSTANDO_MINUTOS_ALARMA:
        DisplayFlashDigits(board->display, 0, 1, PERIODO_PARPADEO);
        break;
    case AJUSTANDO_HORAS_ALARMA:
        DisplayFlashDigits(board->display, 2, 3, PERIODO_PARPADEO);
        // DisplayToggleDot(board->display,0);
        // DisplayToggleDot(board->display,1);
        // DisplayToggleDot(board->display,2);
        // DisplayToggleDot(board->display,3);
        
        break;  
    default:
        break;
    }
}



int main(void){
    uint8_t entrada[4];//Vector en el cual guardaremos el valor de entrada y lo que mostraremos mientras configuro la hora
    reloj =ClkCreate(TICS_POR_SEGUNDO, ToggleAlarma);
    board = BoardCreate();

    CambiarModo(SIN_CONFIGURAR);

    SisTick_Init(TICS_POR_SEGUNDO);
    DisplayFlashDigits(board->display, 0, 3, PERIODO_PARPADEO);

    while(true){

        //BOTON ACEPTAR
        if(DigitalInputHasActivate(board->accept)){
            if(sonando_alarma){
                ToggleAlarma(reloj);
                PosponerAlarma(reloj,POSPONER_MINUTOS,sonando_alarma);
            }else{
                if(modo==MOSTRANDO_HORA){
                    ClkActivateAlarma(reloj,1);
                }
                if(modo==AJUSTANDO_MINUTOS_ACTUAL){//<! Si estoy configurando los minutos y apreto acceptar paso a configurar la hora
                    CambiarModo(AJUSTANDO_HORAS_ACTUAL);
                }else
                if(modo==AJUSTANDO_HORAS_ACTUAL){

                    ClkSetTime(reloj, entrada, sizeof(entrada));//<! Si estoy configurando la hora y apreto aceptar, termino de configurar quedo mostrando hora
                    CambiarModo(MOSTRANDO_HORA);
                }else
                if(modo==AJUSTANDO_MINUTOS_ALARMA){//<! Si estoy configurando los minutos y apreto acceptar paso a configurar la hora
                    CambiarModo(AJUSTANDO_HORAS_ALARMA);
                }else
                if(modo==AJUSTANDO_HORAS_ALARMA){

                    ClkSetAlarma(reloj, entrada, sizeof(entrada));//<! Si estoy configurando la hora y apreto aceptar, termino de configurar quedo mostrando hora
                    CambiarModo(MOSTRANDO_HORA);
                }
            }
        }
        
        //BOTON CANCELAR
        if (DigitalInputHasActivate(board->cancel)){
            if(sonando_alarma){
                ToggleAlarma(reloj);
            }else{
                if(modo==MOSTRANDO_HORA){
                    ClkActivateAlarma(reloj,0);
                }else{
                    if(ClkGetTime(reloj, entrada, sizeof(entrada))){//Si me devuelve 1 es porque es valida y 0 porque es invalida
                        CambiarModo(MOSTRANDO_HORA);//Si la hora es valida y cancelo la configuracion de alarma u hora, vuelvo a mostrar hora
                    }else{
                        CambiarModo(SIN_CONFIGURAR); //Si la hora es invalida y cancelo la configuracion, vuelvo a sin configurar
                    }
                }
            }
        }

        //BOTON INCREMENTAR
        if(DigitalInputHasActivate(board->increment)){
            if((modo==AJUSTANDO_HORAS_ACTUAL)||(modo==AJUSTANDO_HORAS_ALARMA)){
                IncrementarBCD(entrada,LIMITE_HORA);
                DisplayWriteBCD(board->display,entrada,sizeof(entrada));
            }else
            if((modo==AJUSTANDO_MINUTOS_ACTUAL)||(modo==AJUSTANDO_MINUTOS_ALARMA)){
                IncrementarBCD(&entrada[2],LIMITE_MINUTO);
                DisplayWriteBCD(board->display,entrada,sizeof(entrada));
            }

        }

        //BOTON DECREMENTAR
        if(DigitalInputHasActivate(board->decrement)){
            if((modo==AJUSTANDO_HORAS_ACTUAL)||(modo==AJUSTANDO_HORAS_ALARMA)){
                DecrementarBCD(entrada,LIMITE_HORA);
                DisplayWriteBCD(board->display,entrada,sizeof(entrada));
            }else
            if((modo==AJUSTANDO_MINUTOS_ACTUAL)||(modo==AJUSTANDO_MINUTOS_ALARMA)){
                DecrementarBCD(&entrada[2],LIMITE_MINUTO);
                DisplayWriteBCD(board->display,entrada,sizeof(entrada));
            }
        }


        //BOTON CONFIGURAR HORA ACTUAL
        if(DigitalInputHasActivate(board->set_time)){
            CambiarModo(AJUSTANDO_MINUTOS_ACTUAL);
            ClkGetTime(reloj, entrada, sizeof(entrada));
            DisplayWriteBCD(board->display,entrada,sizeof(entrada));
        }


        //BOTON CONFIGURAR ALARMA
        if(DigitalInputHasActivate(board->set_alarma)){
            CambiarModo(AJUSTANDO_MINUTOS_ALARMA);
            ClkGetAlarma(reloj, entrada, sizeof(entrada));
            DisplayWriteBCD(board->display,entrada,sizeof(entrada));
        }
    

        for (int index = 0; index < 20; index++) {
            for (int delay = 0; delay < 25000; delay++) {
                __asm("NOP");
            }
        }
    }
}

void SysTick_Handler(void){
    static uint16_t contador=0;
    uint8_t hora[4];
    bool llave=false;
    DisplayRefresh(board->display);
    ClkTick(reloj);

    contador = (contador+1)%TICS_POR_SEGUNDO;
    if(contador>=TICS_POR_SEGUNDO/2){
        llave=true;
    }else{
        llave=false;
    }
    if(modo<=MOSTRANDO_HORA){ //Solo muestra hora en mostrando hora y configurar
        ClkGetTime(reloj, hora, sizeof(hora));
        DisplayWriteBCD(board->display,hora, sizeof(hora));
        if(llave){
            //DisplaySetDot(board->display,1);
                if(ClkGetAlarma(reloj,hora,sizeof(hora))){
                    //DisplaySetDot(board->display,3);
            }
        }
    }

}


