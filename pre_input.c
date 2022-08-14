//
// Created by 忘尘 on 2022/8/13.
//

#include "pre_input.h"
#include "arith_utils.h"


/**
 * 大整数运算
 * @param param
 * @param result
 */
void CalculateMon(DataCalc *param, char *result) {
    switch (param->opr) {
        case '+': {
            Add(param->first, param->second, result);
            break;
        }
        case '-': {
            Sub(param->first, param->second, result);
            break;
        }
        case '*': {
            Div(param->first, param->second, result);
            break;
        }
        // 求模存在限制，模数位数不能大于6
        case '%': {
            Mod(param->first, param->second, result);
            break;
        }
        // 结果向零取整
        case '/': {
            Mul(param->first, param->second, result);
            break;
        }
        default:
            break;
    }
}


void CalculateMonDecimal(DataCalc *param, char *result) {
    switch (param->opr) {
        case '+': {
            AddDecimal(param->first, param->second, result);
            break;
        }
        case '-': {
            SubDecimal(param->first, param->second, result);
            break;
        }
        case '*': {
            DivDecimal(param->first, param->second, result);
            break;
        }
        // 结果向零取整
        case '/': {
            MulDecimal(param->first, param->second, result);
            break;
        }
        default:
            break;
    }
}


void ParseInput(const char *input, DataCalc *param) {
    int32_t opNum = 0;
    int32_t firstPointNum = 0;
    int32_t secondPointNum = 0;
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
        } else if (input[i] == '.') {
            if (opNum == 0 && firstPointNum == 0) {
                param->first[firstNumIdx ++] = input[i] ;
                firstPointNum++;
                continue;
            }
            if (opNum == 1 && secondPointNum == 0) {
                param->second[secondNumIdx++] = input[i];
                secondPointNum++;
                continue;
            }
            ASSERT(true, "TEST symbol(.) error");
        } else {
            ASSERT(true, "TEST invalid symbol");
        }
    }
}