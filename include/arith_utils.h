//
// Created by 忘尘 on 2022/8/13.
//

#ifndef ARITHMETIC_UTILS_H
#define ARITHMETIC_UTILS_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#define ASSERT(expr, log)                                                  \
do  {                                                                      \
    if ((expr) > 0) {                                                      \
        printf("%s [%s:%d]\n", log, __FUNCTION__, __LINE__);               \
        exit(0);                                                           \
    }                                                                      \
} while(0)

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) > (b) ? (b) : (a))

bool IsDigit(char ch);
void Reverse(char *s);

#endif //ARITHMETIC_UTILS_H
