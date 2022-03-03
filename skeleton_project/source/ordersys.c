#include "ordersys.h"

void newOrder(OrderSys* order_sys, Floor floor, ButtonType order_type){
    //Sjekk?
    order_sys->orders[floor][order_type]=t;
}
/**
 * @brief Get the Next Order object, 
 * @warning May get stuck in function. Allways make sure that orders has at least one order when using
 * @param orders 
 * @return Floor 
 */

Floor getNextOrder(OrderSys* order_sys){
    for(int floor=0;floor<N_FLOORS;floor++){
        for(int order_num=0; order_num<N_ORDER_TYPES; order_num++){
            if(order_sys->orders[floor][order_num] == t){
                Floor dest = floor;
                return dest;
            }
        }
    }
    return undefined;
}
void orderComplete(OrderSys* order_sys, Floor current_floor){
    for(int i=0; i<N_ORDER_TYPES; i++){
        if(order_sys->orders[current_floor][i] == t){
            order_sys->orders[current_floor][i] = f;
        }
        
    }
}
void orderSysinit(OrderSys* order_sys){
    for(int i=0; i<N_FLOORS;i++){
        for (int j=0; j<N_ORDER_TYPES;j++){
            order_sys->orders[i][j] = f;
        }
    }
    order_sys->nextOrder = undefined;
}

