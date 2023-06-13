#include "digital.h"
#include <stdint.h>
#include <stdbool.h>
#include "pantalla.h"

// Creo el struct tipo board
typedef struct board_s{
	digital_output_t buzzer;
	digital_input_t set_time;
	digital_input_t set_alarma;
	digital_input_t decrement;
	digital_input_t increment;
	digital_input_t accept;
	digital_input_t cancel;
	display_t display;
	
} * board_t; //La direccion de memoria del puntero y los almacenado es constante


board_t BoardCreate(void);


void SisTick_Init(uint16_t ticks);
