#include "elevator.h"
#include "utils.h"

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
Elevator elevatorInit(Elevator* elevator){
    for(int i=0; i<N_FLOORS;i++){
        for (int j=0; j<N_ORDER_TYPES;j++){
            elevator->order_queue[i][j] = f;
        }
    }
    elevator->obstructed    = f;
    elevator->stop_btn      = f;
    elevator->dir           = DIRN_STOP;
    elevator->num_orders    = 0;
    elevator->door_open     = f;
    elevator->current_floor =undefined;
}
void nextAction(Elevator* elevator){
    Floor current_order =   getNextOrder(&(elevator->order_queue));
    Bool data_vector[NUM_STATE_VARIABLES] = {elevator->door_open,
                                            getElevatorFloor(elevator)>current_order,
                                            getElevatorFloor(elevator)<current_order,
                                            getElevatorFloor(elevator)==current_order,
                                            elevator->stop_btn};
    Bool state_table[NUM_STATE_VARIABLES][NUM_ACTIONS]; 
    columnWiseAnd(data_vector, mask_table, state_table);
    Bool rules_fulfiled[NUM_ACTIONS];
    columWiseComparison(state_table, condidtion_table, rules_fulfiled);
    for(int i=0; i<NUM_ACTIONS; i++){
        if(rules_fulfiled[i] == t){
            executeAction(i, elevator);
        }
    }
}

void executeAction(int action_num, Elevator* elevator){
    if(action_num == 0){
        elevator->dir = DIRN_UP;
        
    }
    else if(action_num == 1){
        elevator->dir = DIRN_DOWN;
    }
    else if(action_num == 2){
        elevator->dir = DIRN_STOP;
    }
    else if(action_num == 3){
        elevator->dir = DIRN_STOP;
    }
}
