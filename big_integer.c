/**
 * 规则： 30位大数运算，其中求模最大位数6位
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_LEN 32
#define MAX_RES_LEN (MAX_LEN << 1)
#define MAX_IN_LEN (MAX_RES_LEN << 1)
#define MOD_TWO_NUM_INTERVAL 4

typedef struct {
    char first[MAX_LEN];
    char second[MAX_LEN];
    char opr;
} DataCalc;

#define CHECK_SYMBOL(val) ((val)[0] == '-' ? -1 : 1)
#define RM_SYMBOL(val) ((char *)(CHECK_SYMBOL(val) == -1 ? (val) + 1 : (val)))

#define ASSERT(expr, log)                                                      \
    do  {                                                                      \
        if ((expr) > 0) {                                                      \
            printf("%s [%s:%d]\n", log, __FUNCTION__, __LINE__);               \
            exit(0);                                                           \
        }                                                                      \
    } while(0)

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

/**
 * 比较两个自然数的最大值
 * @param first
 * @param second
 * @return > ret 1; < ret -1; = ret 0
 */
int32_t CompNumStrSize(const char *first, const char *second) {
    int32_t len1 = (int32_t) strnlen(first, MAX_LEN);
    int32_t len2 = (int32_t) strnlen(second, MAX_LEN);
    int32_t flag;
    if (len1 > len2) {
        flag = 1;
    } else if (len1 < len2) {
        flag = -1;
    } else {
        flag = strncmp(first, second, MAX_LEN);
    }
    return flag;
}

/**
 * 获取两个自然数的长度最大值
 * @param input
 * @param param
 */
int32_t GetStrMaxLen(const char *first, const char *second) {
    int32_t len1 = (int32_t) strnlen(first, MAX_LEN);
    int32_t len2 = (int32_t) strnlen(second, MAX_LEN);
    return len1 > len2 ? len1 : len2;
}

void ParseInput(const char *input, DataCalc *param) {
    int32_t opNum = 0;
    int32_t firstNumIdx = 0;
    int32_t secondNumIdx = 0;
    for (int32_t i = 0; i < strnlen(input, MAX_IN_LEN); i++) {
        if (IsDigit(input[i])) {
            ASSERT(opNum > 1, "TEST input err");
            ASSERT((firstNumIdx > MAX_LEN - 1) || (secondNumIdx > MAX_LEN - 1), "TEST too long param");
            if (opNum == 0) {
                param->first[firstNumIdx++] = input[i];
            }
            if (opNum == 1) {
                param->second[secondNumIdx++] = input[i];
            }
        } else if (input[i] == '-') {
            ASSERT(firstNumIdx > 0 && secondNumIdx > 0 && opNum > 0, "TEST param err");
            if (opNum == 0 && firstNumIdx > 0 && secondNumIdx == 0) {
                opNum++;
                param->opr = input[i];
                continue;
            }
            ASSERT((firstNumIdx > MAX_LEN - 1) || (secondNumIdx > MAX_LEN - 1), "TEST too long param");
            if (opNum == 0 && firstNumIdx == 0) {
                param->first[firstNumIdx++] = input[i];
            }
            if (opNum == 1 && secondNumIdx == 0) {
                param->second[secondNumIdx++] = input[i];
            }
        } else if (input[i] == '+' || input[i] == '*' || input[i] == '%' || input[i] == '/') {
            ASSERT(firstNumIdx == 0 || opNum > 1, "TEST too many symbol");
            opNum++;
            param->opr = input[i];
        } else {
            ASSERT(true, "TEST invalid symbol");
        }
    }
}

/**
 * 满足条件: 自然数 + 自然数
 * @param first
 * @param second
 * @param result
 */
void AddTwoNum(char *first, char *second, char *result) {
    int32_t maxLen = GetStrMaxLen(first, second);
    char remainder;
    Reverse(first);
    Reverse(second);
    for (int32_t i = 0; i < maxLen; ++i) {
        result[i] = (char) (first[i] + second[i]);
    }

    for (int32_t i = 0; i < maxLen + 1 && result[i] != '\0'; ++i) {
        remainder = (char) (result[i] % '0' + '0');
        if (remainder > '9') {
            result[i + 1]++;
            result[i] = (char) (remainder - 10);
        } else {
            result[i] = remainder;
        }
    }
    // 还原
    Reverse(first);
    Reverse(second);
    Reverse(result);
}


/**
 * 满足条件： 大自然数 - 小自然数整数（first > second）
 * @param first
 * @param second
 * @param result
 */
void SubTwoNum(char *first, char *second, char *result) {
    int32_t maxLen = GetStrMaxLen(first, second);
    Reverse(first);
    Reverse(second);
    for (int32_t i = 0; i < maxLen; ++i) {
        result[i] = (first[i] - second[i]) % '0' + '0';
    }
    for (int32_t i = 0; i < maxLen; ++i) {
        if (result[i] < '0') {
            result[i + 1]--;
            result[i] += 10;
        }
    }
    // 删除前缀冗余零
    for (int32_t i = maxLen - 1; i > 0; --i) {
        if (result[i] == '0') {
            result[i] = '\0';
        } else {
            break;
        }
    }
    Reverse(first);
    Reverse(second);
    Reverse(result);
}

void AddPlus(char *result, char *val) {
    char first[MAX_LEN] = {'\0'};
    char second[MAX_LEN] = {'\0'};
    memcpy(first, result, MAX_LEN);
    memcpy(second, val, MAX_LEN);
    AddTwoNum(first, second, result);
}

void SubPlus(char *result, char *val) {
    char first[MAX_LEN] = {'\0'};
    char second[MAX_LEN] = {'\0'};
    memcpy(first, result, MAX_LEN);
    memcpy(second, val, MAX_LEN);
    SubTwoNum(first, second, result);
}

void DivTwoNum(char *first, char *second, char *result) {
    int32_t i, j, k;
    int32_t firstLen = (int32_t) strnlen(first, MAX_LEN);
    int32_t secondLen = (int32_t) strnlen(second, MAX_LEN);
    k = secondLen + firstLen;
    int tmp[MAX_RES_LEN] = {0};
    Reverse(first);
    Reverse(second);
    for (i = 0; i < firstLen; i++) {
        for (j = 0; j < secondLen; j++) {
            tmp[i + j] += ((first[i] - '0') * (second[j] - '0'));
        }
    }

    for (i = 0; i <= k; i++) {
        if (tmp[i] > 9) {
            tmp[i + 1] += tmp[i] / 10;
            tmp[i] %= 10;
        }
    }
    for (i = 0; i < k; ++i) {
        result[i] += tmp[i] + '0';
    }
    for (i = k; i >= 0; i--) {
        if (result[i] == '0') {
            result[i] = '\0';
        }
        if (result[i] != '\0' && result[i] != '0') {
            break;
        }
    }
    Reverse(first);
    Reverse(second);
    Reverse(result);
}

void MulTwoNum(char *first, char *second, char *result) {
    int len2 = (int32_t)strnlen(second, MAX_LEN);
    char pow[MAX_LEN] = {'\0'};
    char result2[MAX_LEN] = {'\0'};
    char second2[MAX_LEN] = {'\0'};
    memcpy(result2, first, MAX_LEN);
    result[0] = '0';
    int count = (int32_t)strnlen(first, MAX_LEN) - (int32_t)strnlen(second, MAX_LEN);
    int num;
    while (count >= 0) {
        num = 0;
        memset(pow, 0, MAX_LEN);
        memcpy(second2, second, MAX_LEN);
        for (int i = 1; i <= count; i++) {
            pow[i] = '0';
            second2[len2 - 1 + i] = '0';
        }
        while (CompNumStrSize(result2, second2) >= 0) {
            SubPlus(result2, second2);
            num++;
        }
        count--;
        if (num == 0) {
            continue;
        }
        pow[0] = (char)('0' + num);
        AddPlus(result, pow);
    }
}

/**
 * 大整数求模
 * @param first
 * @param second
 * @param result
 */
void ModTwoNumV2(char *first, char *second, char *result) {
    memcpy(result, first, MAX_LEN);
    char second2[MAX_LEN] = {'\0'};
    int count = (int32_t)strnlen(first, MAX_LEN) - (int32_t)strnlen(second, MAX_LEN);
    int len2 = (int32_t)strnlen(second, MAX_LEN);
    while (count >= 0) {
        memcpy(second2, second, MAX_LEN);
        for (int i = 0; i < count; ++i) {
            second2[len2 + i] = '0';
        }
        while (CompNumStrSize(result, second2) >= 0) {
            SubPlus(result, second2);
        }
        count--;
    }
}

/**
 * 满足条件： second位数 <= 6
 * @param first
 * @param second
 * @param result
 */
void ModTwoNum(char *first, char *second, char *result) {
    uint32_t sum = 0;
    uint32_t mod = strtod(second, NULL);
    int32_t len = (int32_t) strnlen(first, MAX_LEN);
    for (int i = 0; i < len; ++i) {
        sum = (sum * 10 + (first[i] - '0')) % mod;
    }
    itoa((int32_t)sum, result, 10);
}

void Add(const DataCalc *param, char *result) {
    int32_t flag1 = CHECK_SYMBOL(param->first);
    int32_t flag2 = CHECK_SYMBOL(param->second);
    if (flag1 == 1 && flag2 == 1) {
        AddTwoNum(RM_SYMBOL(param->first), RM_SYMBOL(param->second), result);
    } else if (flag1 * flag2 < 0) {
        int32_t max = CompNumStrSize(RM_SYMBOL(param->first), RM_SYMBOL(param->second));
        /**
         * -2 + 1
         *  2 + -1
         *  -1 + 2
         *  1 + -2
         */
        if (max == 1) {
            if (flag1 < 0) {
                result[0] = '-';
                SubTwoNum(RM_SYMBOL(param->first), RM_SYMBOL(param->second), result + 1);
            } else {
                SubTwoNum(RM_SYMBOL(param->first), RM_SYMBOL(param->second), result);
            }

        } else {
            if (flag2 < 0) {
                result[0] = '-';
                SubTwoNum(RM_SYMBOL(param->second), RM_SYMBOL(param->first), result + 1);
            } else {
                SubTwoNum(RM_SYMBOL(param->second), RM_SYMBOL(param->first), result);
            }
        }

    } else {
        result[0] = '-';
        AddTwoNum(RM_SYMBOL(param->first), RM_SYMBOL(param->second), result + 1);
    }
}


void Sub(DataCalc *param, char *result) {
    param->opr = '+';
    int32_t flag2 = CHECK_SYMBOL(param->second);
    int32_t len2 = (int32_t) strlen(param->second);
    if (flag2 == -1) {
        for (int i = 0; i < len2; ++i) {
            if (i == len2 - 1) {
                param->second[i] = '\0';
            } else {
                param->second[i] = param->second[i + 1];
            }
        }
    } else {
        for (int32_t i = len2; i >= 0; --i) {
            if (i == 0) {
                param->second[i] = '-';
            } else {
                param->second[i] = param->second[i - 1];
            }
        }
    }
    Add(param, result);
}

void Mul(DataCalc *param, char *result) {
    ASSERT(strcmp(param->second, "0") == 0, "TEST divisor cannot be zero");
    ASSERT(strcmp(param->second, "-0") == 0, "TEST divisor cannot be zero");

    int32_t flag1 = CHECK_SYMBOL(param->first);
    int32_t flag2 = CHECK_SYMBOL(param->second);
    if (flag1 * flag2 < 0) {
        result[0] = '-';
        MulTwoNum(RM_SYMBOL(param->first), RM_SYMBOL(param->second), result + 1);
    } else {
        MulTwoNum(RM_SYMBOL(param->first), RM_SYMBOL(param->second), result);
    }
    if (strcmp("-0", result) == 0) {
        result[0] = '0';
        result[1] = '\0';
    }
}


void Div(DataCalc *param, char *result) {
    uint32_t i;
    int flag1 = CHECK_SYMBOL(param->first);
    int flag2 = CHECK_SYMBOL(param->second);
    DivTwoNum(RM_SYMBOL(param->first), RM_SYMBOL(param->second), result);
    if (flag1 * flag2 < 0) {
        for (i = strnlen(result, MAX_RES_LEN); i > 0; --i) {
            result[i] = result[i - 1];
        }
        result[0] = '-';
    }
}

//  (a + b) % p = (a % p + b % p) % p => a * b % p = (a % p) % p
void Mod(DataCalc *param, char *result) {
    int32_t flag1 = CHECK_SYMBOL(param->first);
    int32_t flag2 = CHECK_SYMBOL(param->second);
    ASSERT(flag1 < 0 || flag2 < 0, "TEST param mod err");
    ASSERT(strcmp(param->second, "0") == 0, "TEST second cannot be zero");
    ASSERT(strcmp(param->second, "-0") == 0, "TEST second cannot be zero");
    char maxIntStr[12] = {'\0'};
    itoa(INT_MAX, maxIntStr, 10);
    if (CompNumStrSize(RM_SYMBOL(param->second), maxIntStr) < 0 &&
    strlen(RM_SYMBOL(param->first)) - strlen(RM_SYMBOL(param->second)) < MOD_TWO_NUM_INTERVAL) {
        ModTwoNum(RM_SYMBOL(param->first), RM_SYMBOL(param->second), result);
    } else {
        ModTwoNumV2(RM_SYMBOL(param->first), RM_SYMBOL(param->second), result);
    }
}

/**
 * 大整数运算
 * @param param
 * @param result
 */
void CalculateMon(DataCalc *param, char *result) {
    switch (param->opr) {
        case '+': {
            Add(param, result);
            break;
        }
        case '-': {
            Sub(param, result);
            break;
        }
        case '*': {
            Div(param, result);
            break;
        }
        // 求模存在限制，模数位数不能大于6
        case '%': {
            Mod(param, result);
            break;
        }
            // 结果向零取整
        case '/': {
            Mul(param, result);
            break;
        }
        default:
            break;
    }
}
int main() {
    char result[MAX_RES_LEN] = {'\0'};
    char input[MAX_IN_LEN] = {'\0'};
    int32_t errCnt = 0;
    int32_t passCnt = 0;
    DataCalc param;
    freopen("../testcase/sum.in", "r", stdin);
    while (scanf("%s\n", input) != EOF) {
        memset(param.first, 0, MAX_LEN);
        memset(param.second, 0, MAX_LEN);
        memset(result, 0, MAX_RES_LEN);
        int resIndex;
        for (int i = 0; i < strnlen(input, MAX_IN_LEN); i++) {
            resIndex = 0;
            if (input[i] == '=') {
                resIndex = i + 1;
                input[i] = '\0';
            }
        }
        ParseInput(input, &param);
        CalculateMon(&param, result);
        if (strcmp(input + resIndex, result) != 0) {
            printf("EXPECT[%s] %s = (res = %s, expect = %s)\n",
                   strcmp(input + resIndex, result) == 0 ? "TRUE" : "FALSE",
                   input, result, input + resIndex);
            errCnt++;
        } else {
            passCnt++;
        }
        memset(input, 0, MAX_RES_LEN);
    }
    printf("EXPECT ALL TESTCASE PASS CNT (pass %d, err %d)\n", passCnt, errCnt);
    return 0;
}
