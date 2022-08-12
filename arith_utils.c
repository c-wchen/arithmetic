//
// Created by 忘尘 on 2022/8/13.
//
#include "include/arith_utils.h"
/**
 * 返回是否是数字类型
 * @param ch
 * @return
 */
bool IsDigit(char ch) {
    if (ch < '0' || ch > '9') {
        return false;
    } else {
        return true;
    }
}

void Reverse(char *s) {
    int32_t len = (int32_t) strlen(s);
    int32_t i = 0;
    char c;
    while (i <= len / 2 - 1) {
        c = s[i];
        s[i] = s[len - 1 - i];
        s[len - 1 - i] = c;
        i++;
    }
}