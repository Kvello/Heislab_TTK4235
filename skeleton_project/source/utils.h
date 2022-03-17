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
#include <stdbool.h>
#define NUM_STATE_VARIABLES 9 //Antall tilstandsvariabler
#define NUM_ACTIONS 8 //Antall aksjoner(regler)
#define t true //Forkortelse
#define f false //Forkortelse

/**
 * @brief Funksjon brukt for å gjøre kollonnevis og mellom @p data_vector og @p table . Resultatet lagres i @p result_table
 * 
 * @param[in] data_vector 
 * @param[in] table 
 * @param[out] result_table 
 */
void columnWiseAnd(bool* data_vector, bool table[][NUM_ACTIONS], bool result_table[][NUM_ACTIONS]);
/**
 * @brief Funksjon brukt for å gjøre kollonvis sammenligning mellom to tabeller @p table1 og @p table2 . Resultatet lagres i @p result_column
 * 
 * @param[in] table1 
 * @param[in] table2 
 * @param[out] result_column 
 */
void columnWiseComparison(bool table1[][NUM_ACTIONS], bool table2[][NUM_ACTIONS], bool* result_column);