#include "elevator.h"

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
    for(int i=0; i<N_FLOORS*N_ORDER_TYPES;i++){
        elevator->order_queue[i%N_FLOORS][i%N_ORDER_TYPES]=f;
    }
    elevator->dir=DIRN_STOP;
    elevator->num_orders=0;
    elevator->current_floor=undefined;
}
