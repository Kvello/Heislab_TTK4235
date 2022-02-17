#pragma once
#include "driver/elevio.h"
#include <inttypes.h>
#include <stdint.h>


/**
 * @brief Hver etasje har max 3 ulike ordretyper, kupe opp, ned
 * 
 */
#define N_ORDER_TYPES 3

/**
 * @brief Struktur for å holde på etasje. Ligger mellom 1, og 4.
 * 
 */
typedef enum Floor {undefined=-1,first=0, second, third, fourth} Floor;
/**
 * @brief Hjelpe struktur for sann/usann verdier
 * 
 */
typedef enum Bool{f, t} Bool;

typedef enum OrderType{Inside, Up, Down} OrderType;

/**
 * @brief tabell av ordre. Hvert element kan være true eller false(1/0), siden hver bestilling kan være bestillt eller ikke.
 * Strukturen til tabellen er slik:
 * 1 etasje | Kupeknapp | Opp | -
 * 2 etasje | Kupeknapp | Opp | Ned
 * 3 etasje | Kupeknapp | Opp | Ned
 * 4 etasje | Kupeknapp | -   | Ned
 */

typedef Bool OrderQueue[N_FLOORS][N_ORDER_TYPES];
typedef struct OrderSys{
    OrderQueue orders;
    uint8_t num_orders;
} OrderSys;

void newOrder(OrderSys*,Floor,OrderType);
Floor getNextOrder(OrderSys*);
void orderComplete(OrderSys*, Floor);


