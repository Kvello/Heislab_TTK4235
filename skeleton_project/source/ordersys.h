/**
 * @file ordersys.h
 * @author Markus Kvello
 * @brief Ordresystem modul. Definerer ordresystemet, og noen funksjoner for å operere på det
 * @version 0.1
 * @date 2022-03-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once
#include "driver/elevio.h"
#include "utils.h"
#include <inttypes.h>
#include <stdint.h>


/**
 * @brief Hver etasje har max 3 ulike ordretyper, kupe opp, ned. Vi øsnker å opperere med ordretyper istedenfor knapptyper, men det er essensiellt det samme
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
typedef bool OrderQueue[N_FLOORS][N_ORDER_TYPES];

/**
 * @brief Ordresystemet. Består av en kø, og en ordre som skal betjenes
 * 
 */
typedef struct OrderSys{
    OrderQueue orders;
    Floor next_order;
} OrderSys;

/**
 * @brief Legger inn en ny ordre i order_sys
 * @param[in] order_type typen knapp @p ButtonType til bestillingen som skal legges inn
 * @param[in] floor etasjen @p Floor til bestillingen som skal leges inn
 * @param[out] order_sys Peker til et ordresystem @p OrderSys
 */
void newOrder(OrderSys* order_sys ,Floor floor, ButtonType order_type);
/**
 * @brief Returnerer etasjen til den neste bestillingen @p next_order fra @p order_sys
 * @param[in] order_sys Peker til et ordresystem
 * @return Floor 
 */
Floor getNextOrder(OrderSys* order_sys);
/**
 * @brief Oppdaterer neste ordre @p next_order i @p order_sys
 * @param[in,out] order_sys Peker til et ordresystem 
 */
void updateNextOrder(OrderSys* order_sys);
/**
 * @brief Fjerner alle bestillinger på etasjen @p floor
 * @param[in] floor Etasjen hvor en bestilling er utført
 * @param[out] order_sys Peker til et ordresystem
 */
void orderComplete(OrderSys* order_sys, Floor floor);
/**
 * @brief Initialiserer ordresystemet @p order_system . Setter alle verdiene i køsystemet @p orders til usann, setter neste ordre @p next_order til @c undefined
 * 
 * @param[out] order_sys Peker til et ordresystem
 */
void orderSysinit(OrderSys* order_sys);
/**
 * @brief sletter alle ordre, og setter neste etasje til @c undefined i ordresystemet @p order_sys
 * 
 * @param[out] order_sys Peker til et ordresystem
 */
void flushOrders(OrderSys* order_sys);
/**
 * @brief returnerer sann hvis det er en bestilling i @p orders på posisjon ( @p floor , @p button ) 
 * 
 * @param[in] order_sys Peker til et ordresystem 
 * @param[in] floor etasjen til bestillingen som skal hentes
 * @param[in] order_type orderetypen @p ButtonType til bestillingen som skal hentes
 * @return bool
 */
bool getOrder(OrderSys* order_sys, Floor floor, ButtonType order_type);
/**
 * @brief Setter verdien av køsystemet @p orders til @p order_sys på posisjon ( @p floor , @p button ) til verdien av @p value
 * 
 * @param[out] order_sys Peker til et ordresystem 
 * @param[in] floor etasjen til bestillingen som skal settes 
 * @param[in] order_type ordretypen @p ButtonType til bestillingen som skal settes 
 * @param[in] value verdien som skal settes 
 */
void setOrder(OrderSys* order_sys, Floor floor, ButtonType order_type, bool value);