#pragma once
#define NUM_STATE_VARIABLES 7
#define NUM_ACTIONS 7

/**
 * @brief Hjelpe struktur for sann/usann verdier
 * 
 */
typedef enum Bool{f, t} Bool;






void columnWiseAnd(Bool* data_vector, Bool table[][NUM_ACTIONS], Bool result_table[][NUM_ACTIONS]);
void columnWiseComparison(Bool table1[][NUM_ACTIONS], Bool table2[][NUM_ACTIONS], Bool* result_column);