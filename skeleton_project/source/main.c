#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "elevator.h"
void checkButtons(Elevator* elevator){
    for(int f = 0; f < N_FLOORS; f++){
        for(int b = 0; b < N_BUTTONS; b++){
            int btnPressed = elevio_callButton(f, b);
            if(btnPressed){
                newOrder(&(elevator->order_system),f , b); // Updates orders when a button is pressed
            }
        }
    }

    if(elevio_obstruction()){
        elevator->obstructed=t;
    } else {
        elevator->obstructed=f;
    }
        
    if(elevio_stopButton()){
        elevator->stop_btn = t;
    }
    else{
        elevator->stop_btn = f;
    }
}

void setLamps(Elevator* elevator){
    if(elevator->current_floor != undefined){
        elevio_floorIndicator(elevator->current_floor); // Lamp lights up when passing new floor
    }
    
    elevio_stopLamp(elevator->stop_btn); // Stoplamp lights up when stop button is pressed
    elevio_doorOpenLamp(elevator->door_open); // Door lamp lights up when door is open
    
    for(int f = 0; f < N_FLOORS; f++){
        for(int b = 0; b < N_BUTTONS; b++){
            elevio_buttonLamp(f, b, elevator->order_system.orders[f][b]); // Lights the lamp of the floors in orders
        }
    }   
}

void updateFloor(Elevator* elevator){
    int floor = elevio_floorSensor();
    if(floor != undefined){
        elevator->current_floor = floor;
        elevator->between_floors = f;
    }
    else if(floor == undefined){
        elevator->between_floors = t;
    }
}

int main(){
    elevio_init();
    Elevator elevator;
    
    printf("=== Elevator ===\n");
    elevatorInit(&elevator);
    while(1){
        updateFloor(&elevator);
        checkButtons(&elevator);
        nextAction(&elevator);
        elevio_motorDirection(elevator.dir);
        setLamps(&elevator);
        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }

    return 0;
}
