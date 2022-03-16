#include "elevator.h"
#include <stdio.h>

/**
 * @brief condition table for determing the elevators actions
 *  statevariables/Rules        |   Up  |   Down    |   Arrived |   Emergency stop  |   Start timer |   Obstructed  |   close door  |   No orders
 *  ----------------------------+-----------------------------------------------------------------------------------------------------------------
 *  Door closed                 |   1   |   1       |   -       |   -               |   1           |   0           |   0           |   -           
 *  next order > current floor  |   1   |   0       |   -       |   -               |   0           |   -           |   -           |   -           
 *  next order < current floor  |   0   |   1       |   -       |   -               |   0           |   -           |   -           |   -           
 *  next order == current floor |   -   |   -       |   -       |   -               |   1           |   -           |   -           |   -       
 *  Stopp button                |   0   |   0       |   
 *  Stop time < 3 (sec)         |   
 *  Obstruction button          |
 *  No orders(next order undef) |
 *  Between floors              |
 *  
 * 
 */
bool condition_table[NUM_STATE_VARIABLES][NUM_ACTIONS] =   {{ t, t, f, f, t, f, f, f},
                                                            { t, f, f, f, f, f, f, f},
                                                            { f, t, f, f, f, f, f, f},
                                                            { f, f, f, f, t, f, f, f},
                                                            { f, f, f, t, f, f, f, f},
                                                            { f, f, t, f, f, f, f, f},
                                                            { f, f, f, f, f, t, f, f},
                                                            { f, f, f, f, f, f, f, t},
                                                            { f, f, f, f, f, f, f, f}};


bool mask_table[NUM_STATE_VARIABLES][NUM_ACTIONS] =    {{ t, t, f, f, t, t, t, f},
                                                        { t, t, f, f, t, f, f, f},
                                                        { t, t, f, f, t, f, f, f},
                                                        { f, f, f, f, t, f, f, f},
                                                        { t, t, t, t, t, f, t, t},
                                                        { f, f, t, f, t, f, t, t},
                                                        { f, f, f, f, f, t, t, f},
                                                        { t, t, f, f, f, f, f, t},
                                                        { f, f, t, f, t, t, f, f}};


/**
 * @brief Get the Elevator Direction object
 * 
 * @param elevator 
 * @return MotorDirection 
 */
MotorDirection getElevatorDirection(Elevator* elevator){
    return elevator->dir;
}

/**
 * @brief Get the Elevator Floor object
 * 
 * @param elevator 
 * @return Floor 
 */
Floor getElevatorFloor(Elevator* elevator){
    return elevator->current_floor;
}

/**
 * @brief Set the Elevator Floor object
 * 
 * @param elevator 
 * @param new_floor 
 */
void setElevatorFloor(Elevator* elevator, Floor new_floor){
    if(new_floor!=undefined){
        elevator->current_floor=new_floor;
    }
    return;
}
/**
 * @brief Set the Elevator Direction object
 * 
 * @param elevator 
 * @param new_dir 
 */
void setElevatorDirection(Elevator* elevator, MotorDirection new_dir){
    elevator->dir=new_dir;
    return;
}

/**
 * @brief Initialization of the elevator, sets all the values, and goes to defined state
 * 
 * @param elevator 
 */
void elevatorInit(Elevator* elevator){
    orderSysinit(&(elevator->order_system));
    elevator->obstructed    = f;
    elevator->stop_btn      = f;
    elevator->dir           = DIRN_STOP;
    elevator->door_open     = f;
    elevator->current_floor = undefined;
    elevator->stop_time     = 0;
    elevator->between_floors= t;
    elevator->emergency     = f;
    elevator->prev_dir      = DIRN_STOP;

    //To get in an defined state
    while(getElevatorFloor(elevator) == undefined){
        setElevatorDirection(elevator, DIRN_UP);
        Floor current_floor = elevio_floorSensor();
        if(current_floor != undefined){
            setElevatorFloor(elevator, elevio_floorSensor());
        }
        elevio_motorDirection(getElevatorDirection(elevator));
    }
}
void updateElevator(Elevator* elevator){
    bool elevator_failed = elevatorSafetyProtocoll(elevator);
    if(elevator_failed == t) return;
    bool rules_fulfiled[NUM_ACTIONS];
    getFullfiledRules(elevator, rules_fulfiled);

/*
    for(int i=0; i<NUM_STATE_VARIABLES; i++){
        printf("datavector[%d]: %d\n",i, data_vector[i]);
    }
*/
    for(int i=0; i<NUM_ACTIONS; i++){
        //printf("rules[%d]: %d\n",i, rules_fulfiled[i]);
        if(rules_fulfiled[i] == t){
            executeRule(i, elevator);
        }
    }
    onwayOrders(elevator);
}
bool elevatorSafetyProtocoll(Elevator* elevator){

    if(elevator->emergency == t){
        updateElevatorOrder(elevator);
        Floor next_order = getNextOrder(&(elevator->order_system));
        Floor current_floor = getElevatorFloor(elevator);
        if(next_order != undefined && next_order != current_floor){
            elevator->emergency = f;
        }else if(next_order == current_floor && elevator->prev_dir != DIRN_STOP){
            if(elevator->between_floors == f){
                elevator->emergency = f;
            }else{
                elevator->emergency = t;
                setElevatorDirection(elevator, -elevator->prev_dir);
            }
        }
        else if(next_order == current_floor && elevator->between_floors == f && elevator->prev_dir == DIRN_STOP){
            elevator->emergency = t;
            setElevatorDirection(elevator, DIRN_STOP);
            setElevatorDoor(elevator, t);
        }else{
            elevator->emergency = t;
        }
    }
    return elevator->emergency;
}
void onwayOrders(Elevator* elevator){
    Floor floor = getElevatorFloor(elevator);
    if(floor == undefined || elevator->between_floors) return;
    switch(elevator->dir){
        case DIRN_DOWN:
            if(getOrder(&(elevator->order_system), getElevatorFloor(elevator), BUTTON_HALL_DOWN) || getOrder(&(elevator->order_system), getElevatorFloor(elevator), BUTTON_CAB)){
                executeRule(arrived, elevator);
                executeRule(start_timer, elevator);
            }
            break;
        case DIRN_UP:
            if(getOrder(&(elevator->order_system), getElevatorFloor(elevator), BUTTON_HALL_UP) || getOrder(&(elevator->order_system), getElevatorFloor(elevator), BUTTON_CAB)){
                executeRule(arrived, elevator);
                executeRule(start_timer, elevator);
            }
            break;
        default:
            return;
    }   
}

void executeRule(Rule rule, Elevator* elevator){
    switch(rule){
        case up:
            setElevatorDirection(elevator, DIRN_UP);
            setElevatorDoor(elevator, f);
            break;
        case down:
            setElevatorDirection(elevator, DIRN_DOWN);
            setElevatorDoor(elevator, f);
            break;
        case arrived:
            setElevatorDirection(elevator, DIRN_STOP);
            updateElevatorOrder(elevator);
            setElevatorDoor(elevator, t);
            elevatorOrderComplete(elevator);
            break;
        case emergency_stop:
            if(getElevatorDirection(elevator) != DIRN_STOP){
                elevator->prev_dir = getElevatorDirection(elevator);
            } 
            elevator->emergency = t;
            flushElevatorOrders(elevator);
            setElevatorDirection(elevator, DIRN_STOP);
            break;
        case start_timer:
            //printf("Starting timer");
            setElevatorDirection(elevator, DIRN_STOP);
            updateElevatorOrder(elevator);
            elevator->stop_time = time(NULL);
            setElevatorDoor(elevator, t);
            elevatorOrderComplete(elevator);
            break;
        case obstructed:
            updateElevatorOrder(elevator);
            setElevatorDoor(elevator, t);
            break;
        case close_door:
            setElevatorDoor(elevator, f);
            break;
        case no_orders:
            updateElevatorOrder(elevator);
            setElevatorDirection(elevator, DIRN_STOP);
            break;
        default:
            break;

    }
}


void updateElevatorOrder(Elevator* elevator){
    updateNextOrder(&(elevator->order_system));
}

void elevatorOrderComplete(Elevator* elevator){
    orderComplete(&(elevator->order_system), getElevatorFloor(elevator));
}

void flushElevatorOrders(Elevator* elevator){
    flushOrders(&(elevator->order_system));
}

void setElevatorDoor(Elevator* elevator, bool val){
    elevator->door_open = val;
}
void getFullfiledRules(Elevator* elevator, bool rules_fulfiled[NUM_ACTIONS]){
    Floor current_order = getNextOrder(&(elevator->order_system));
    bool data_vector[NUM_STATE_VARIABLES] = {!elevator->door_open,
                                            current_order>getElevatorFloor(elevator),
                                            current_order<getElevatorFloor(elevator),
                                            getElevatorFloor(elevator)==current_order,
                                            elevator->stop_btn,
                                            difftime(time(NULL),elevator->stop_time)<3,
                                            elevator->obstructed,
                                            current_order == undefined,
                                            elevator->between_floors};

    bool state_table[NUM_STATE_VARIABLES][NUM_ACTIONS]; 
    columnWiseAnd(data_vector, mask_table, state_table);
    bool rules_fulfiled[NUM_ACTIONS];
    columnWiseComparison(state_table, condition_table, rules_fulfiled);
}
