#include "elevator.h"
#include <stdio.h>
Bool condition_table[NUM_STATE_VARIABLES][NUM_ACTIONS] =   {{ t, t, f, f, t, f, f, f},
                                                            { t, f, f, f, f, f, f, f},
                                                            { f, t, f, f, f, f, f, f},
                                                            { f, f, f, f, t, f, f, f},
                                                            { f, f, f, t, f, f, f, f},
                                                            { f, f, t, f, f, f, f, f},
                                                            { f, f, f, f, f, t, f, f},
                                                            { f, f, f, f, f, f, f, t}};


Bool mask_table[NUM_STATE_VARIABLES][NUM_ACTIONS] =    {{ t, t, f, f, t, t, t, f},
                                                        { t, t, f, f, t, f, f, f},
                                                        { t, t, f, f, t, f, f, f},
                                                        { t, t, f, f, t, f, f, f},
                                                        { t, t, t, t, t, f, t, t},
                                                        { f, f, t, f, t, f, t, t},
                                                        { f, f, f, f, f, t, t, t},
                                                        { t, t, f, f, t, f, f, t}};


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
    printf("Current order: %d, current floor: %d\n", current_order, getElevatorFloor(elevator));
    Bool data_vector[NUM_STATE_VARIABLES] = {!elevator->door_open,
                                            current_order>getElevatorFloor(elevator),
                                            current_order<getElevatorFloor(elevator),
                                            getElevatorFloor(elevator)==current_order,
                                            elevator->stop_btn,
                                            difftime(time(NULL),elevator->stop_time)<3,
                                            elevator->obstructed,
                                            current_order == undefined};
    Bool state_table[NUM_STATE_VARIABLES][NUM_ACTIONS]; 
    columnWiseAnd(data_vector, mask_table, state_table);
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

void executeAction(Rules rule, Elevator* elevator){
    switch(rule){
        case up:
            elevator->dir = DIRN_UP;
            break;
        case down:
            elevator->dir = DIRN_DOWN;
            break;
        case arrived:
            elevator->dir = DIRN_STOP;
            orderComplete(&(elevator->order_system), elevator->current_floor);
            break;
        case emergency_stop:
            for(int i=0; i<N_FLOORS; i++){
                orderComplete(&(elevator->order_system), i);
            }
            elevator->dir = DIRN_STOP;
            break;
        case start_timer:
            elevator->dir = DIRN_STOP;
            orderComplete(&(elevator->order_system), elevator->current_floor);
            elevator->stop_time = time(NULL);
            elevator->door_open = t;
            break;
        case obstructed:
            elevator->door_open = t;
            break;
        case close_door:
            elevator->door_open = f;
            break;
        case no_orders:
            printf("no orders\n");
            elevator->dir = DIRN_STOP;
            elevator->door_open = f;

    }
}

void setLamps(Elevator* elevator){
    elevio_floorIndicator(elevator->current_floor); // Lamp lights up when passing new floor
    elevio_stopLamp(elevator->stop_btn); // Stoplamp lights up when stop button is pressed
    elevio_doorOpenLamp(elevator->door_open); // Door lamp lights up when door is open
    
    for(int f = 0; f < N_FLOORS; f++){
        for(int b = 0; b < N_BUTTONS; b++){
            int btnPressed = elevio_callButton(f, b);
            if(btnPressed){
                newOrder(&(elevator->order_system),f , b);              
            }
            elevio_buttonLamp(f, b, elevator->order_system.orders[f][b]); // Lights the lamp of the floors in orders
        }
    }
}