//
// Created by 忘尘 on 2022/8/13.
//
#include "arith_utils.h"
#include "big_decimal.h"
#include "big_integer.h"

/**
 * 获取小数位数，没有小数位返回0
 * @param ch
 * @return
 */
int32_t GetDecimalPlaces(char *ch) {
    int32_t len = (int32_t) strnlen(ch, MAX_LEN);
    for (int i = 0; i < len; ++i) {
        if (ch[i] == '.') {
            return len - 1 - i;
        }
    }
    return 0;
}

/**
 * 删除头部为零的数字
 * @param ch
 */
void DelHeadZero(char *ch) {
    int32_t len = (int32_t) strnlen(ch, MAX_LEN);
    int count = 0;
    while (ch[count] == '0') {
        count++;
    }
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

/**
 * 删除尾部为零的数字
 * @param ch
 */
void DelTailZero(char *ch) {
    int len = (int32_t) strnlen(ch, MAX_LEN);
    for (int i = len - 1; i >= 0; --i) {
        if (ch[i] == '0') {
            ch[i] = '\0';
        } else {
            break;
        }
    }
}

/**
 * 删除小数点
 * @param ch
 */
void DelDecimalPoint(char *ch) {
    int idx = GetDecimalPlaces(ch);
    int32_t len = (int32_t) strnlen(ch, MAX_LEN);
    if (idx > 0) {
        for (int i = len - 1 - idx; i < len; ++i) {
            ch[i] = ch[i + 1];
        }
        ch[len - 1] = '\0';
    }
    DelHeadZero(ch);
}

/**
 * 截断字符串idx后面部分数字
 * @param ch
 * @param idx
 */
void TruncateTailNum(char *ch, int32_t idx) {
    int32_t len = (int32_t) strnlen(ch, MAX_LEN);
    for (int i = idx; i < len; ++i) {
        ch[i] = '\0';
    }
}

/**
 * 保留reversedBits位小数
 * @param ch
 * @param reversedBits 保留位数
 */
void BigDecimalRound(char *ch, int reversedBits) {
    int len = (int32_t) strnlen(ch, MAX_LEN);
    int idx = GetDecimalPlaces(ch);
    if (reversedBits < 0 || (len - idx) + reversedBits > MAX_LEN) {
        return;
    }
    int reversedPos = len - 1 - idx + reversedBits;
    if (idx > reversedBits && ch[reversedPos + 1] >= '5') {
        if (ch[reversedPos] < '9') {
            ch[reversedPos] = (char) (ch[reversedPos] + 1);
        } else {
            char result[MAX_RES_LEN] = {0};
            char decimalOne[MAX_LEN] = {0};
            for (int i = 0; i < reversedBits + 2; ++i) {
                decimalOne[i] = '0';
            }
            decimalOne[1] = '.';
            decimalOne[reversedBits + 1] = '1';
            if (CHECK_SYMBOL(ch)) {
                AddDecimal(ch, decimalOne, result);
            } else {
                SubDecimal(ch, decimalOne, result);
            }
            memcpy_s(ch, MAX_LEN, result, MAX_LEN);
        }
    }
    TruncateTailNum(ch, reversedPos + 1);
    idx = GetDecimalPlaces(ch);
    len = (int32_t) strnlen(ch, MAX_LEN);
    if (idx < reversedBits) {
        for (int i = 0; i < reversedBits - idx; ++i) {
            ch[len + i] = '0';
        }
    }
}


void RemoveRight(char *ch, int size, int grid) {
    int len = (int32_t) strnlen(ch, MAX_LEN);
    for (int i = 0; i < size; ++i) {
        if (i >= len) {
            break;
        }
        ch[len - 1 - i + grid] = ch[len - 1 - i];
    }
}

int32_t AlignTwoNumPadZero(char *first, char *second, bool isPadZero) {
    int firstPointIdx = GetDecimalPlaces(first);
    int secondPointIdx = GetDecimalPlaces(second);
    DelDecimalPoint(first);
    DelDecimalPoint(second);
    int firstLen = (int32_t) strnlen(first, MAX_LEN);
    int secondLen = (int32_t) strnlen(second, MAX_LEN);
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
    int resLen = (int32_t) strlen(result);
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

void MulDecimal(char *first, char *second, char *result) {
    (void) AlignTwoNumPadZero(RM_SYMBOL(first), RM_SYMBOL(second), false);
    Mul(first, second, result);
    // Mul返回零没有正负之分。
    if (CompNumStrSize(result, "0") == 0 && CHECK_SYMBOL(first) * CHECK_SYMBOL(second) < 0) {
        result[0] = '-';
        result[1] = '0';
    }
    char tmpFirst[MAX_LEN] = {0};
    char modResult[MAX_RES_LEN] = {0};
    char mulResult[MAX_RES_LEN] = {0};
    int idx = (int32_t) strlen(result);
    bool flag = false;
    memcpy_s(tmpFirst, MAX_LEN, first, MAX_LEN);
    for (int i = 0; i < REVERSED_BITS + REVERSED_INTERVAL; ++i) {
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
    BigDecimalRound(result, REVERSED_BITS);
}

