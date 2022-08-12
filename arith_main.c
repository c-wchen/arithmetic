#include "include/big_integer.h"
#include "include/pre_input.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>
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
