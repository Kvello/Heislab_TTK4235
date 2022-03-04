#pragma once
#include "driver/elevio.h"
#include "utils.h"
#include <inttypes.h>
#include <stdint.h>


/**
 * @brief Hver etasje har max 3 ulike ordretyper, kupe opp, ned
 * 
 */
#define N_ORDER_TYPES N_BUTTONS

/**
 * @brief Struktur for å holde på etasje. Ligger mellom 1, og 4.
 * 
 */
typedef enum Floor {undefined=-1,first=0, second, third, fourth} Floor;



/**
 * @brief tabell av ordre. Hvert element kan være true eller false(1/0), siden hver bestilling kan være bestillt eller ikke.
 * Strukturen til tabellen er slik:
 * 1 etasje | Opp |  -  | Kupeknapp
 * 2 etasje | Opp | Ned | Kupeknapp
 * 3 etasje | Opp | Ned | Kupeknapp
 * 4 etasje |  -  | Ned | Kupeknapp
 */

typedef Bool OrderQueue[N_FLOORS][N_ORDER_TYPES];
typedef struct OrderSys{
    OrderQueue orders;
    Floor nextOrder;
} OrderSys;

void newOrder(OrderSys*,Floor,ButtonType);
Floor getNextOrder(OrderSys*);
void updateNextOrder(OrderSys*);
void orderComplete(OrderSys*, Floor);
void orderSysinit(OrderSys* order_sys);
void flushOrders(OrderSys* order_sys);
Bool getOrder(OrderSys*, Floor, ButtonType);
void setOrder(OrderSys*, Floor, ButtonType, Bool);