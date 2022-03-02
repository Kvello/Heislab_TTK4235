#pragma once
#include "ordersys.h"





typedef struct elevator
{
    OrderSys order_system;
    uint8_t num_orders;
    MotorDirection dir;
    Floor current_floor;
    Bool  obstructed;
    Bool stop_btn;
    Bool door_open;
} Elevator;

MotorDirection getElevatorDirection(Elevator*);
Floor getElevatorFloor(Elevator*);
void setElevatorFloor(Elevator*, Floor);
void setElevatorDirection(Elevator*, MotorDirection);
void elevatorInit(Elevator*);
void nextAction(Elevator*);
void executeAction(int, Elevator*);
