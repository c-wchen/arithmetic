//
// Created by 忘尘 on 2022/8/13.
//
#include "arith_utils.h"
#include "big_decimal.h"
#include "big_integer.h"

int32_t GetDecimalPointIndex(char *ch) {
    int len = strlen(ch);
    for (int i = 0; i < len; ++i) {
        if (ch[i] == '.') {
            return len - 1 - i;
        }
    }
    return 0;
}

void DelDecimalPoint(char *ch) {
    int idx = GetDecimalPointIndex(ch);
    int len = strlen(ch);
    if (idx > 0) {
        for (int i = len - 1 - idx; i < len; ++i) {
            ch[i] = ch[i + 1];
        }
        ch[len - 1] = '\0';
    }
}

void DelHeadZero(char *ch) {
    int32_t len = strlen(ch);
    int count = 0;
    while (ch[count] != '\0' && ch[count] == '0') {
        count++;
    };
    if (count == 0) {
        return;
    }
    for (int i = 0; i < len; ++i) {
        if (i >= len - count) {
            ch[i] = '\0';
        } else {
            ch[i] = ch[count + i];
        }
    }
}

void DelTailZero(char *ch) {
    int len = strlen(ch);
    for (int i = len - 1; i >= 0; --i) {
        if (ch[i] == '0') {
            ch[i] = '\0';
        } else {
            break;
        }
    }
}

void RemoveRight(char *ch, int size, int grid) {
    int len = strlen(ch);
    for (int i = 0; i < size; ++i) {
        if (i >= len) {
            break;
        }
        ch[len - 1 - i + grid] = ch[len - 1 - i];
    }
}

int32_t AlignTwoNumPadZero(char *first, char *second, bool isPadZero) {
    int firstPointIdx = GetDecimalPointIndex(first);
    int secondPointIdx = GetDecimalPointIndex(second);
    DelDecimalPoint(first);
    DelDecimalPoint(second);
    DelHeadZero(first);
    DelHeadZero(second);
    int firstLen = strlen(first);
    int secondLen = strlen(second);
    int zeroPadLen = firstPointIdx - secondPointIdx;
    if (isPadZero) {
        return firstPointIdx + secondPointIdx;
    }
    if (zeroPadLen < 0) {
        for (int i = 0; i < -zeroPadLen; ++i) {
            first[firstLen + i] = '0';
        }
    } else {
        for (int i = 0; i < zeroPadLen; ++i) {
            second[secondLen + i] = '0';
        }
    }
    return MAX(firstPointIdx, secondPointIdx);
}

void ProcResult(char *result, int32_t rightLen) {
    if (rightLen == 0) {
        return;
    }
    int resLen = strlen(result);
    if (rightLen < resLen) {
        RemoveRight(result, rightLen, 1);
        result[resLen - rightLen] = '.';
    } else {
        RemoveRight(result, resLen, rightLen - resLen + 2);
        for (int i = 0; i < rightLen - resLen + 2; ++i) {
            result[i] = '0';
        }
        result[1] = '.';
    }
    DelTailZero(result);
}

void AddDecimal(char *first, char *second, char *result) {

    int rightLen = AlignTwoNumPadZero(RM_SYMBOL(first), RM_SYMBOL(second), false);
    Add(first, second, result);
    ProcResult(RM_SYMBOL(result), rightLen);
}

void SubDecimal(char *first, char *second, char *result) {
    int rightLen = AlignTwoNumPadZero(RM_SYMBOL(first), RM_SYMBOL(second), false);
    Sub(first, second, result);
    ProcResult(RM_SYMBOL(result), rightLen);
}

void DivDecimal(char *first, char *second, char *result) {
    int32_t rightLen = AlignTwoNumPadZero(RM_SYMBOL(first), RM_SYMBOL(second), true);
    Div(first, second, result);
    ProcResult(RM_SYMBOL(result), rightLen);
}

#define REVERSE_BITS 7

void MulDecimal(char *first, char *second, char *result) {
    if (strcmp("7669.9246", first) == 0) {
        printf("test");
    }
    (void) AlignTwoNumPadZero(RM_SYMBOL(first), RM_SYMBOL(second), false);
    Mul(first, second, result);
    if (CompNumStrSize(result, "0") == 0 && CHECK_SYMBOL(first) * CHECK_SYMBOL(second) < 0) {
        result[0] = '-';
        result[1] = '0';
    }
    char tmpFirst[MAX_LEN] = {0};
    char modResult[MAX_RES_LEN] = {0};
    char mulResult[MAX_RES_LEN] = {0};
    int idx = strlen(result);
    bool flag = false;
    memcpy_s(tmpFirst, MAX_LEN, first, MAX_LEN);
    for (int i = 0; i < REVERSE_BITS; ++i) {
        if (i == 0) {
            result[idx++] = '.';
        }
        if (flag) {
            result[idx++] = '0';
            continue;
        }
        memset(modResult, 0, MAX_RES_LEN);
        Mod(RM_SYMBOL(tmpFirst), RM_SYMBOL(second), modResult);
        memcpy_s(tmpFirst, MAX_LEN, modResult, MAX_LEN);
        if (CompNumStrSize(modResult, "0") == 0) {
            flag = true;
            result[idx++] = '0';
            continue;
        }
        tmpFirst[strlen(tmpFirst)] = '0';
        memset(mulResult, 0, MAX_RES_LEN);
        Mul(RM_SYMBOL(tmpFirst), RM_SYMBOL(second), mulResult);
        result[idx++] = mulResult[0];
    }
}

