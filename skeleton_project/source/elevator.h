#pragma once
#include "ordersys.h"
#include "driver/elevio.h"
#include <time.h>

typedef enum rules{up=0, down=1, arrived=2, emergency_stop=3, start_timer=4, obstructed=5 , close_door=6, no_orders=7} Rules; 



typedef struct elevator
{
    OrderSys order_system;
    uint8_t num_orders;
    MotorDirection dir;
    Floor current_floor;
    Bool  obstructed;
    Bool stop_btn;
    Bool door_open;
    time_t stop_time;
} Elevator;

MotorDirection getElevatorDirection(Elevator*);
Floor getElevatorFloor(Elevator*);
void setElevatorFloor(Elevator*, Floor);
void setElevatorDirection(Elevator*, MotorDirection);
void elevatorInit(Elevator*);
void nextAction(Elevator*);
void executeAction(Rules, Elevator*);
void checkButtons(Elevator*);
void setLamps(Elevator*);