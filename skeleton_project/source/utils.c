/**
 * @file utils.c
 * @author Markus Kvello 
 * @brief Implementasjonsfil for hjelpemodul
 * @version 0.1
 * @date 2022-03-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "utils.h"
void columnWiseAnd(bool* data_vector, bool table[][NUM_ACTIONS], bool result_table[][NUM_ACTIONS]){
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
void columnWiseComparison(bool table1[][NUM_ACTIONS], bool table2[][NUM_ACTIONS], bool* result_column){

    for(int i=0; i<NUM_ACTIONS; i++){
        int j=0;
        for(j=0; j<NUM_STATE_VARIABLES; j++){
            if(table1[j][i] != table2[j][i]) break;
        }
        if(j==NUM_STATE_VARIABLES){
            result_column[i] = t;
        }else{
            result_column[i] = f;
        }
    }
}