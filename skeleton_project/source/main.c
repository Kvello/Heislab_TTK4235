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
        elevator.current_floor = elevio_floorSensor();
        printf("floor: %d \n",elevator.current_floor);
/*
        if(elevator.current_floor == 0){
            elevio_motorDirection(DIRN_UP);
        }

        if(elevator.current_floor == N_FLOORS-1){
            elevio_motorDirection(DIRN_DOWN);
        }
*/

        for(int f = 0; f < N_FLOORS; f++){
            for(int b = 0; b < N_BUTTONS; b++){
                int btnPressed = elevio_callButton(f, b);
                newOrder(&(elevator.order_system),f , b);
                elevio_buttonLamp(f, b, btnPressed);
            }
        }

        if(elevio_obstruction()){
            elevator.obstructed=t;
            elevio_stopLamp(1);
        } else {
            elevator.obstructed=f;
            elevio_stopLamp(0);
        }
        
        if(elevio_stopButton()){
            elevator.stop_btn = t;;
            break;
        }
        nextAction(&elevator);
        elevio_motorDirection(elevator.dir);
        
        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }

    return 0;
}
