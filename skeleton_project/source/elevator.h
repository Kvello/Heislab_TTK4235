#pragma once
#include "ordersys.h"
#include "driver/elevio.h"
#include "utils.h"
#include <stdint.h>
#include <inttypes.h>

#define NUM_STATE_VARIABLES 5
#define NUM_ACTIONS 4

Bool condidtion_table[NUM_STATE_VARIABLES][NUM_ACTIONS] =   {{ t, t, t, f},
                                                            { t, f, f, f},
                                                            { f, t, f, f},
                                                            { f, f, f, t}};
Bool mask_table[NUM_STATE_VARIABLES][NUM_ACTIONS] =     {{t, t, t, f},
                                                        {t, t, t, f},
                                                        {t, t, t, f},
                                                        {t, t, t, t}};

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
