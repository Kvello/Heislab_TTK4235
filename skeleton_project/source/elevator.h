#pragma once
#include "ordersys.h"
#include <time.h>

typedef enum actions{up=0, down, stop,emergency_stop , start_timer, open_door, close_door} Action; 



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
void executeAction(Action, Elevator*);
