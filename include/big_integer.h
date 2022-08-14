//
// Created by 忘尘 on 2022/8/12.
//

#ifndef ARITHMETIC_BIG_INTEGER_H
#define ARITHMETIC_BIG_INTEGER_H
#define MAX_LEN 32
#define MAX_RES_LEN (MAX_LEN << 1)
#define MAX_IN_LEN (MAX_RES_LEN << 1)

#define CHECK_SYMBOL(val) ((val)[0] == '-' ? -1 : 1)
#define RM_SYMBOL(val) ((char *)(CHECK_SYMBOL(val) == -1 ? (val) + 1 : (val)))

void Add(char *first, char *second, char *result);
void Sub(char *first, char *second, char *result);
void Mul(char *first, char *second, char *result);
void Div(char *first, char *second, char *result);
void Mod(char *first, char *second, char *result);

int CompNumStrSize(const char *first, const char *second);
#endif //ARITHMETIC_BIG_INTEGER_H
