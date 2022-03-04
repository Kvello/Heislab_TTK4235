#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "elevator.h"


int main(){
    elevio_init();
    Elevator elevator;
    
    printf("=== Elevator ===\n");
    elevatorInit(&elevator);
    while(1){
        int floor = elevio_floorSensor();
        if(floor != undefined){
            elevator.current_floor = floor;
            elevator.between_floors = f;
        }
        else if(floor == undefined){
            elevator.between_floors = t;
        }
        
        checkButtons(&elevator);
        nextAction(&elevator);
        elevio_motorDirection(elevator.dir);
        setLamps(&elevator);
        
        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }

    return 0;
}
