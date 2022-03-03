#include "elevator.h"
#include <stdio.h>
Bool condition_table[NUM_STATE_VARIABLES][NUM_ACTIONS] =   {{ t, t, f, f, t, f, f},
                                                            { t, f, f, f, f, f, f},
                                                            { f, t, f, f, f, f, f},
                                                            { f, f, f, f, t, f, f},
                                                            { f, f, f, t, f, f, f},
                                                            { f, f, t, f, f, f, f},
                                                            { f, f, f, f, f, t, f}};


Bool mask_table[NUM_STATE_VARIABLES][NUM_ACTIONS] =    {{ t, t, t, t, t, f, f},
                                                        { t, f, t, t, f, t, t},
                                                        { f, t, t, t, f, t, t},
                                                        { f, f, t, t, t, t, t},
                                                        { f, f, f, t, f, t, f},
                                                        { t, t, t, t, f, t, f},
                                                        { t, t, t, t, t, t, f}};


MotorDirection getElevatorDirection(Elevator* elevator){
    return elevator->dir;
}
Floor getElevatorFloor(Elevator* elevator){
    return elevator->current_floor;
}
void setElevatorFloor(Elevator* elevator, Floor new_floor){
    if(new_floor!=undefined){
        elevator->current_floor=new_floor;
    }
    return;
}
void setElevatorDirection(Elevator* elevator, MotorDirection new_dir){
    elevator->dir=new_dir;
    return;
}
void elevatorInit(Elevator* elevator){
    for(int i=0; i<N_FLOORS;i++){
        for (int j=0; j<N_ORDER_TYPES;j++){
            elevator->order_system.orders[i][j] = f;
        }
    }
    elevator->obstructed    = f;
    elevator->stop_btn      = f;
    elevator->dir           = DIRN_STOP;
    elevator->num_orders    = 0;
    elevator->door_open     = f;
    elevator->current_floor = undefined;
    elevator->stop_time     = 0;
}
void nextAction(Elevator* elevator){
    Floor current_order =   getNextOrder(&(elevator->order_system));
    Bool data_vector[NUM_STATE_VARIABLES] = {elevator->door_open,
                                            getElevatorFloor(elevator)>current_order,
                                            getElevatorFloor(elevator)<current_order,
                                            getElevatorFloor(elevator)==current_order,
                                            elevator->stop_btn};
    Bool state_table[NUM_STATE_VARIABLES][NUM_ACTIONS]; 
    columnWiseAnd(data_vector, state_table, state_table);
    Bool rules_fulfiled[NUM_ACTIONS];
    columnWiseComparison(state_table, condition_table, rules_fulfiled);

    for(int i=0; i<NUM_STATE_VARIABLES; i++){
        printf("datavector[%d]: %d\n",i, data_vector[i]);
    }

    for(int i=0; i<NUM_ACTIONS; i++){
        printf("rules[%d]: %d\n",i, rules_fulfiled[i]);
        if(rules_fulfiled[i] == t){
            executeAction(i, elevator);
        }
    }
}

void executeAction(Action action, Elevator* elevator){
    switch(action){
        case up:
            elevator->dir = DIRN_UP;
        case down:
            elevator->dir = DIRN_DOWN;
        case stop:
            elevator->dir = DIRN_STOP;
            orderComplete(&(elevator->order_system), elevator->current_floor);
        case emergency_stop:
            elevator->dir = DIRN_STOP;
        case start_timer:
            elevator->stop_time = time(NULL);
        case open_door:
            elevator->door_open = t;
        case close_door:
            elevator->door_open = f;
    }
}
