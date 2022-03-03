#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "elevator.h"


int main(){
    elevio_init();
    Elevator elevator;
    elevatorInit(&elevator);
    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

    while(1){
        int floor = elevio_floorSensor();
        if(floor != undefined){
            elevator.current_floor = floor;
        }
        
        //printf("floor: %d \n",elevator.current_floor);
/*
        if(elevator.current_floor == 0){
            elevio_motorDirection(DIRN_UP);
        }

        if(elevator.current_floor == N_FLOORS-1){
            elevio_motorDirection(DIRN_DOWN);
        }
*/

        // for(int f = 0; f < N_FLOORS; f++){
        //     for(int b = 0; b < N_BUTTONS; b++){
        //         int btnPressed = elevio_callButton(f, b);
        //         if(btnPressed){
        //             newOrder(&(elevator.order_system),f , b);
                    
        //         }
        //         elevio_buttonLamp(f, b, elevator.order_system.orders[f][b]);
        //     }
        // }



        if(elevio_obstruction()){
            elevator.obstructed=t;
        } else {
            elevator.obstructed=f;
        }
        
        if(elevio_stopButton()){
            elevator.stop_btn = t;
        }
        nextAction(&elevator);
        elevio_motorDirection(elevator.dir);
        setLamps(&elevator);
        //elevio_doorOpenLamp(elevator.door_open);
        
        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }

    return 0;
}
