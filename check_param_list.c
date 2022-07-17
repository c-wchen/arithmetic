//
// Created by 忘尘 on 2022/7/17.
//
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>

#define MAX_BUF_SIZE 256
bool CheckParamFromAddr(const char *func, uint32_t lineNum, int32_t num, ...) {
    va_list valist;
    va_start(valist, num);
    char buf[MAX_BUF_SIZE] = {'\0'};
    int32_t offset = 0;
    offset += snprintf(buf + offset, MAX_BUF_SIZE - offset, "Check Param[%s:%d] ", func, lineNum);
    for (int i = 0; i < num; ++i) {
        uint64_t addr = va_arg(valist, uint64_t);
        if (addr == 0) {
            if (i == 0) {
                offset += snprintf(buf + offset, MAX_BUF_SIZE - offset, "param%d is INVALID", i);
            } else {
                offset += snprintf(buf + offset, MAX_BUF_SIZE - offset, ", param%d is INVALID", i);
            }
        }
    }
    buf[MAX_BUF_SIZE - 1] = '\0';
    printf_s("%s\n", buf);
    va_end(valist);
}

#define PARAM_ONE     1
#define PARAM_TWO     2
#define PARAM_THREE   3
#define PARAM_FOUR    4
#define PARAM_FIVE    5
#define PARAM_SIX     6
#define PARAM_SEVEN   7
#define PARAM_EIGHT   8
#define PARAM_NINE    9

#define CHECK_ADDR(num, ...) CheckParamFromAddr(__FUNCTION__, __LINE__, num, __VA_ARGS__)



void test1() {
    uint64_t a = 0;
    uint64_t b = 90;
    uint64_t c = 0;
    CHECK_ADDR(PARAM_THREE, a, b, c);
}

void test2(int a, int b, int c, int d, int e) {
    char *ptr = &a;
    printf("%p %p %p %p %p\n", &a, &b, &c, &d, &e);
    printf("%llu %llu %llu %llu %llu\n", *ptr, *(ptr + 8), *(ptr + 16), *(ptr + 24), *(ptr + 32));
}

int main() {
    test1();
    test2(10, 9, 8, 7, 6);
    return 0;
}