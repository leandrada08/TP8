

#include "bsp.h"
#include "reloj.h"
#include <stdbool.h>
#include <stddef.h>


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


/*Definicion de variable publicas*/
static board_t board;

static clk_t reloj;

static modo_t modo;

/*Definicion de variables privada*/

/*Imprementacion de funciones publicas*/
void ActivarAlarma(clk_t reloj){

}


int main(void){
    uint8_t hora[6]; // Vector con el que consultaremos la hora

    reloj =ClkCreate(1000, ActivarAlarma);
    
    board = BoardCreate();

    modo = SIN_CONFIGURAR;

    SysTick_Init(1000);
    DisplayFlashDigits(board->display, 0, 3, 200);

    while(true){
        if(DigitalInputHasActivate(board->decrement)|DigitalInputHasActivate(board->increment)){

        }
        if(DigitalInputHasActivate(board->accept)){

        }
        
        if (DigitalInputHasActivate(board->cancel)|DigitalInputHasActivate(board->set_alarma)){

        }
        if(DigitalInputHasActivate(board->set_time)){

        }

        for (int index = 0; index < 100; index++) {
            for (int delay = 0; delay < 5000; delay++) {
                __asm("NOP");
            }
        }

        /*
        ClkGetTime(reloj.hora,sizeof(hora));
        __asm volatile("cpsid i");
        DisplayWriteBCD(board->display,hora, sizeof(hora));
        __asm volatile("cpsid i");;
        */
    }
}



void SysTick_Handler(void){
    static bool last_value =false;
    bool current_value;
    uint8_t hora[6];

    DisplayRefresh(board->display);
    current_value = ClockNewTick(reloj);// Nos indica cuando pasa medio segundo

    if(current_value!=last_value){ //Verifico si paso medio segundo
        last_value=current_value;

        if(modo<=MOSTRANDO_HORA){
            ClkGetTime(reloj, hora, sizeof(hora));
            DisplayWriteBCD(board->display,hora, sizeof(hora));
            DisplayToggleDot(board->display,1);
        }
    }

}
