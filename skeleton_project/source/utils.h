#pragma once

/**
 * @brief Hjelpe struktur for sann/usann verdier
 * 
 */
typedef enum Bool{f, t} Bool;

void columnWiseAnd(Bool* data_vector, Bool table[][], Bool result_table[][]);
void columnWiseComparison(Bool table1[][], Bool table2[][], Bool* result_column);