#pragma once
#include "ordersys.h"
#include "driver/elevio.h"
#include <time.h>
/**
 * @brief regler som vi har definert. Se besutningstabell. Vi har valgt å gi reglene navn, da de ganske spesifikke oppgaver/bruksområder
 * 
 */
typedef enum rules{up=0, down=1, arrived=2, emergency_stop=3, start_timer=4, obstructed=5 , close_door=6, no_orders=7} Rule; 


/**
 * @brief Tilstandsmaskin. Struct for å holde på tilstandsvarablene
 * 
 */
typedef struct elevator
{
    OrderSys order_system;
    MotorDirection dir;
    Floor current_floor;
    bool between_floors;
    bool  obstructed;
    bool stop_btn;
    bool emergency;
    bool door_open;
    time_t stop_time;
    MotorDirection prev_dir;
} Elevator;
/**
 * @brief henter motor reningen @c dir til @p elevator 
 * @param[in] elevator peker til heisobjekt @c Elevator
 * @return @c MotorDirection 
 */
MotorDirection getElevatorDirection(Elevator* elevator);
/**
 * @brief Henter etasjen @p current_floor til heisobjektet gitt av @p elevator
 * 
 * @param[in] elvator peker til heisobjekt @p Elevator 
 * @return Floor 
 */
Floor getElevatorFloor(Elevator* elvator);
/**
 * @brief Setter etasjen @c current_floor til heisobjektet gitt av @p elevator
 * 
 * @param[out] elvator peker til heisobjekt @c Elevator 
 * @param[in] floor verdien etasjen @c current_floor skal settes til 
 */
void setElevatorFloor(Elevator* elvator, Floor floor);
/**
 * @brief setter retningen @c dir til heisobjektet gitt av @p elevator til @p new_dir
 * 
 * @param[out] elevator peker til heisobjekt @c Elevator 
 * @param[in] new_dir retningen @c MotorDirection som @c dir skal settes til 
 */
void setElevatorDirection(Elevator* elevator, MotorDirection new_dir);
/**
 * @brief Initialisering av heisobjektet gitt av @p elevator . Initialiserer ordersystemet @c order_system .  Setter verdier til alle tilstandsvariablene. Forsøker å få heisen i en definert tilstand
 * 
 * @param[out] elevator peker til heisobjekt @c Elevator  
 */
void elevatorInit(Elevator* elevator);
/**
 * @brief Sjekker oppflyte regler, og utfører de. Endrer på tilstnadsmaskinen gitt av @p elevator
 * 
 * @param[in, out] elevator peker til heisobjekt @c Elevator 
 */
void updateElevator(Elevator* elevator);
/**
 * @brief gjennomfører regel nummer @p rule
 * 
 * @param[in] rule regel @c Rule som skal utføres
 * @param[out] elevator elevator peker til heisobjekt @c Elevator 
 */
void executeRule(Rule rule, Elevator* elevator);
/**
 * @brief Sjekker for bestillinger i samme retning som heisen
 * 
 * @param elevator 
 */
void onwayOrders(Elevator* elevator);
/**
 * @brief Oppdaterer ordresystemet @c order_system til heisen @p elevator
 * 
 * @param[out, in] elevator peker til heisobjekt @c Elevator  
 */
void updateElevatorOrder(Elevator* elevator);
/**
 * @brief Sletter alle ordre i ordresystemet @c order_system på etasjen til heisen gitt av @p elevator
 * 
 * @param[out] elevator peker til heisobjekt @c Elevator
 */
void elevatorOrderComplete(Elevator* elevator);
/**
 * @brief Sletter alle ordre i ordresystemet @c order_system til heisen gitt av @p elevator
 * 
 * @param[out] elevator peker til heisobjekt @c Elevator
 */
void flushElevatorOrders(Elevator* elevator);
/**
 * @brief Setter verdien av @c door_open til heisen gitt av @p elevator
 * 
 * @param[out] elevator peker til heisobjekt @c Elevator
 */
void setElevatorDoor(Elevator* elevator, bool);
/**
 * @brief Protokoll for hvis heisen er i nødmodus. Prøver å komme ut av en nødmodus, returnerer sann hvis heisen er i en nødmodus, returnerer usann ellers
 * 
 * @param[in, out] elevator peker til heisobjekt @c Elevator
 * @return bool 
 */
bool elevatorSafetyProtocoll(Elevator* elevator);
/**
 * @brief Sjekker hvilke regler som er oppfylte, og skriver sann til disse i @p rules_fulfilled
 * 
 * @param[in] elevator peker til heisobjekt @c Elevator
 * @param[out] rules_fulfilled array av lengde @c NUM_ACTIONS for de tilfredstillte reglene
 */
void getFullfilledRules(Elevator* elevator, bool rules_fullfilled[NUM_ACTIONS]);

