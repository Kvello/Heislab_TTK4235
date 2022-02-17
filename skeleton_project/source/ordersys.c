#include "ordersys.h"

void newOrder(OrderSys* order_sys, Floor floor, OrderType order_type){
    //Sjekk?
    order_sys->orders[floor][order_type]=t;
    order_sys->num_orders++;
}
/**
 * @brief Get the Next Order object, 
 * @warning May get stuck in function. Allways make sure that orders has at least one order when using
 * @param orders 
 * @return Floor 
 */

Floor getNextOrder(OrderSys* order_sys){
    int i=0;
    Floor dest;
    while(i<N_FLOORS*N_ORDER_TYPES){
        if(order_sys->orders[i%N_FLOORS][i%N_ORDER_TYPES]){
            dest=i%N_FLOORS;

            return dest;
        }
    }
}
void orderComplete(OrderSys* order_sys, Floor current_floor){
    for(int i=0; i<N_ORDER_TYPES; i++){
        if(order_sys->orders[current_floor][i]){
            order_sys->orders[current_floor][i]=f;
            order_sys->num_orders--;
        }
        
    }
}


