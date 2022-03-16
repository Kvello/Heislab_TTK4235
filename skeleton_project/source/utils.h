/**
 * @file utils.h
 * @author Markus Kvello 
 * @brief Hjelpemodul. Definerer logikk nødvendig for beslutningstabellen
 * @version 0.1
 * @date 2022-03-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once
#define NUM_STATE_VARIABLES 9
#define NUM_ACTIONS 8
#include <stdbool.h>
#define t true
#define f false


void columnWiseAnd(bool* data_vector, bool table[][NUM_ACTIONS], bool result_table[][NUM_ACTIONS]);
void columnWiseComparison(bool table1[][NUM_ACTIONS], bool table2[][NUM_ACTIONS], bool* result_column);