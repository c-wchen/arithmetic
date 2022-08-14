//
// Created by 忘尘 on 2022/8/13.
//

#ifndef ARITHMETIC_PRE_INPUT_H
#define ARITHMETIC_PRE_INPUT_H
#include "big_integer.h"
#include "big_decimal.h"
typedef struct {
    char first[MAX_LEN];
    char second[MAX_LEN];
    char opr;
} DataCalc;

void CalculateMon(DataCalc *param, char *result);
void CalculateMonDecimal(DataCalc *param, char *result);
void ParseInput(const char *input, DataCalc *param);

#endif //ARITHMETIC_PRE_INPUT_H
