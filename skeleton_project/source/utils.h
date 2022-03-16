#pragma once
#define NUM_STATE_VARIABLES 9
#define NUM_ACTIONS 8
#include <stdbool.h>
#define t true
#define f false

/**
 * @brief Hjelpe struktur for sann/usann verdier
 * 
 */
bool a = true;






void columnWiseAnd(bool* data_vector, bool table[][NUM_ACTIONS], bool result_table[][NUM_ACTIONS]);
void columnWiseComparison(bool table1[][NUM_ACTIONS], bool table2[][NUM_ACTIONS], bool* result_column);