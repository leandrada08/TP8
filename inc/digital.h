#ifndef DIGITAL_H
#define DIGITAL_H

/* Librerías necesarias */
#include <stdint.h>
#include <stdbool.h>

/* Macros útiles */
#define MAX_VALOR 100
#define MIN_VALOR 0

/** @brief Estructura de pin de salida
 * 
 */
typedef struct digital_output_s * digital_output_t;
/** @brief Estructura de pin de entrada
 * 
 */
typedef struct digital_input_s * digital_input_t;



/*Declaracion de funciones para la salida.Declaro los metodos que usare para los pines de salida */
/** @brief Metodo para crear salida
 * 
 * @param port Puerto GPIO con la salida
 * @param pin Numero de terminal del puntero GPIO de la salida
 * @return digital_output_t Puntero al descriptor de salida 
*/
digital_output_t DigitalOutputCreate(uint8_t port, uint8_t pin);


/** @brief Metodo para desactivar salida
 * 
 * @param output Puntero al descriptor de la salida
*/
void DigitalOutputDesactivate(digital_output_t output);


/** @brief Metodo para activar salida
 * 
 * @param output Puntero al descriptor de la salida
 * 
*/
void DigitalOutputActivate(digital_output_t output);


/** @brief Metodo para invertir estado de salida
 * 
 * @param output Puntero al descriptor de la salida
 * 
*/
void DigitalOutputToggle(digital_output_t output);


/** @brief Metodo para crear entrada
 * 
 * @param port Puerto GPIO con la entrada
 * @param pin Numero de terminal del puntero GPIO de la entrada
 * @return digital_output_t Puntero al descriptor de entrada 
*/
digital_input_t DigitalInputCreate(uint8_t port, uint8_t pin);


/** @brief Metodo para ver estado de una entrada
 * 
 * @param input Puntero al descriptor de la entrada
 * @return true La entrada esta activa
 * @return false La entrada esta inactiva
 */
bool DigitalInputGetState(digital_input_t input);


/** @brief Metodo para ver cambios en una entrada entrada
 * 
 * @param input Puntero al descriptor de la entrada
 * @return true La entrada cambio
 * @return false La entrada no cambio
*/
bool DigitalInputHasChange(digital_input_t input);


/** @brief Metodo para ver si la entrada esta activa
 * 
 * @param input Puntero al descriptor de la entrada
 * @return true La entrada tuvo activacion
 * @return false La entrada no tuvo activacion
*/
bool DigitalInputHasActivate(digital_input_t input);



/** @brief Metodo para ver si la entrada esta desactiva
 * 
 * @param input Puntero al descriptor de la entrada
 * @return true La entrada tuvo desactivacion
 * @return false La entrada no tuvo desactivacion
*/
bool DigitalInputHasDesactivated(digital_input_t input);



#endif /* EJEMPLO_H */
