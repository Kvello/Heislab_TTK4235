#include "ordersys.h"

void newOrder(OrderSys* order_sys, Floor floor, ButtonType order_type){
    //Sjekk?
    order_sys->orders[floor][order_type]=t;
}
/**
 * @brief Updates the Next Order object, 
 * @param OrderSys* 
 * @return void
 */

void updateNextOrder(OrderSys* order_sys){
    for(int floor=0;floor<N_FLOORS;floor++){
        for(int button_type=0; button_type<N_ORDER_TYPES; button_type++){
            if(getOrder(order_sys, floor, button_type) == t){
                order_sys->nextOrder = floor;
                return;
            }
        }
    }
    return;
}
/**
 * @brief Get the Next Order object
 * 
 * @param order_sys 
 * @return Floor 
 */
Floor getNextOrder(OrderSys* order_sys){
    return order_sys->nextOrder;
}

/**
 * @brief removes all orders on given floor
 * 
 * @param order_sys 
 * @param current_floor 
 */
void orderComplete(OrderSys* order_sys, Floor current_floor){
    if(current_floor == undefined) return;
    for(int i=0; i<N_ORDER_TYPES; i++){
        if(getOrder(order_sys, current_floor, i) == t){
            setOrder(order_sys, current_floor, i, f);
        }
        
    }
}
void orderSysinit(OrderSys* order_sys){
    for(int i=0; i<N_FLOORS;i++){
        for (int j=0; j<N_ORDER_TYPES;j++){
            setOrder(order_sys, i, j, f);
        }
    }
    order_sys->nextOrder = undefined;
}

void flushOrders(OrderSys* order_sys){
    for(int i=0; i<N_FLOORS; i++){
        orderComplete(order_sys, i);
    }
    order_sys->nextOrder = undefined;
}

Bool getOrder(OrderSys* order_sys, Floor floor, ButtonType button){
    return order_sys->orders[floor][button];
}

void setOrder(OrderSys* order_sys, Floor floor, ButtonType button, Bool set){
    order_sys->orders[floor][button] = set;
}