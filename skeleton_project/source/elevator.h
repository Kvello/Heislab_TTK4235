#pragma once
#include "ordersys.h"
#include "driver/elevio.h"
#include "utils.h"
#include <stdint.h>
#include <inttypes.h>

Bool decision_table[4][6] = {{ t, f, t, f, t, t},
                            { t, t, t, f, f, t},
                            { t, t, f, t, t ,t},
                            { t, t, t, f, f, t}};

typedef struct elevator
{
    OrderQueue order_queue;
    uint8_t num_orders;
    MotorDirection dir;
    Floor current_floor;
    Bool  obstructed;
    Bool stop_btn;
} Elevator;

MotorDirection getElevatorDirection(Elevator*);
Floor getElevatorFloor(Elevator*);
void setElevatorFloor(Elevator*, Floor);
void setElevatorDirection(Elevator*, MotorDirection);
Elevator elevatorInit(Elevator*);
void makeDecision(Elevator*);
