#include "ordersys.h"

void newOrder(OrderSys* order_sys, Floor floor, ButtonType order_type){
    order_sys->orders[floor][order_type]=t;
}

void updateNextOrder(OrderSys* order_sys){
    for(int floor=0;floor<N_FLOORS;floor++){
        for(int button_type=0; button_type<N_ORDER_TYPES; button_type++){
            if(getOrder(order_sys, floor, button_type) == t){
                order_sys->next_order = floor;
                return;
            }
        }
    }
    return;
}

Floor getNextOrder(OrderSys* order_sys){
    return order_sys->next_order;
}

void orderComplete(OrderSys* order_sys, Floor floor){
    if(floor == undefined) return;
    order_sys->next_order = undefined;
    for(int i=0; i<N_ORDER_TYPES; i++){
        if(getOrder(order_sys, floor, i) == t){
            setOrder(order_sys, floor, i, f);
        }
        
    }
}
void orderSysinit(OrderSys* order_sys){
    for(int i=0; i<N_FLOORS;i++){
        for (int j=0; j<N_ORDER_TYPES;j++){
            setOrder(order_sys, i, j, f);
        }
    }
    order_sys->next_order = undefined;
}

void flushOrders(OrderSys* order_sys){
    for(int i=0; i<N_FLOORS; i++){
        orderComplete(order_sys, i);
    }
    order_sys->next_order = undefined;
}

bool getOrder(OrderSys* order_sys, Floor floor, ButtonType order_type){
    return order_sys->orders[floor][order_type];
}

void setOrder(OrderSys* order_sys, Floor floor, ButtonType order_type, bool value){
    order_sys->orders[floor][order_type] = value;
}