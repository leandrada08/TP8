#include <stdbool.h>
#include <stdint.h>
#include <string.h>

typedef struct clk_s * clk_t;

typedef void(*suena_alarma_t)(clk_t);

/** @brief Funcion para crear un reloj
 * @param tics_por_segundo: Cuantos tics del micro seran un segundo en nuestro reloj
 * @param suena_alarma_t 
 * @return Nos devuelve un puntero al reloj creado
 * Esta funcion nos inicia un espacio del tamanio clk_s con 0
*/
clk_t ClkCreate(int tics_por_segundo,suena_alarma_t gestor_alarma);


/** @brief Funcion para ver la hora de un reloj
 * @param clk_t reloj: Puntero al reloj que necesitamos ver la hora
 * @param uint8_t hora: Vector donde la funcion nos devolvera la hora
 * @param int size: Tamanio de la hora que queremos ver
 * @return Nos devuelve 1 si la hora es valida o 0 si es invalida
 *
*/
bool ClkGetTime(clk_t reloj, uint8_t * hora, int size);


/** @brief Funcion para modificar la hora del reloj
 * Esta funcion nos devuelve 1 o 0 si el reloj es invalido o valido
 * @param clk_t reloj
 * @param uint8_t hora
 * @param int size
 *
*/
void ClkSetTime(clk_t reloj, const uint8_t * hora, int size);



/**
 * @brief Funcion para contar segundo, en esta funcion tambien verifico si la alarma suena
 * Le mandamos el reloj y nos cuenta 1 segundo en el reloj dado
 * 
 * @param reloj Reloj del cual tenemos que contar un tick

 */
void ClkTick(clk_t reloj);

/**
 * @brief Funcion para ver la hora de la alarma
 * 
 * @param reloj 
 * @param hora 
 * @param sizeof 
 * @return true Si la alarma esta activada(si ya fue configurada)
 * @return false Si la alarma esta desactiva(si no fue configurada)
 */
bool ClkGetAlarma(clk_t reloj,uint8_t * hora, int size);

/**
 * @brief  Funcion para configurar la hora de la alarma
 * 
 * @param reloj 
 * @param hora 
 * @param size 
 */
void ClkSetAlarma(clk_t reloj,const uint8_t * hora, int size);

/**
 * @brief Funcion para activar o desactivar la hora
 * 
 * @param reloj Reloj del cual queremos configurar la alarma
 * @param estado 0 si la queremos desactivar y 1 si la queremos activar
 */
void ClkActivateAlarma(clk_t reloj,bool estado);



/**
 * @brief funcion para posponer alarma una cantidad arbitraria de minutos
 * 
 * @param reloj : Reloj al cual se le desea posponer la alarma
 * @param posponer  : Minutos que queremos posponer la alarma
 * @param estado : Estado de la alarma
 */
void PosponerAlarma(clk_t reloj,uint8_t posponer, bool estado);

/**
 * @brief Funcion para que la alarma deje de sonar
 * 
 * @param reloj Reloj al cual deseamos apagar la alarma
 */
void ApagarAlarma(clk_t reloj);
