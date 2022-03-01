#include "utils.h"
#include "elevator.h"

void columnWiseAnd(Bool* data_vector, Bool** table, Bool** result_table){
    for(int i=0; i<NUM_STATE_VARIABLES; i++)
        for(int j=0; j<NUM_ACTIONS; j++){
            if(data_vector[i] && table[i][j]){
                result_table[i][j] = t;
            }
            else{
                result_table[i][j] = f;
            }
        }
}
void columnWiseComparison(Bool** table1, Bool** table2, Bool* result_column){
    for(int i=0; i<NUM_ACTIONS; i++){
        int j=0;
        for(j; j<NUM_STATE_VARIABLES; j++){
            if(table1[j][i] != table2[j][i]) break;
        }
        if(j==NUM_ACTIONS){
            result_column[i] = t;
        }else{
            result_column[i] = f;
        }
    }
}