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
    elevator->current_floor =undefined;
}
void makeDecision(Elevator* elevator){
    current_order = getNextOrder(&(elevator->order_queue))
    Bool data_vector[4][1] =   {{getElevatorFloor(elevator)>current_order},
                                {getElevatorFloor(elevator)=current_order},}; 
}
