#pragma once
#include "ordersys.h"
#include "driver/elevio.h"
#include <stdint.h>
#include <inttypes.h>

typedef struct elevator
{
    OrderQueue order_queue;
    uint8_t num_orders;
    MotorDirection dir;
    Floor current_floor;
} Elevator;

MotorDirection getElevatorDirection(Elevator*);
Floor getElevatorFloor(Elevator*);
void setElevatorFloor(Elevator*, Floor);
void setElevatorDirection(Elevator*, MotorDirection);
Elevator elevatorInit(Elevator*);
