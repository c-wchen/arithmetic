"""
生成四则运算表达式
"""
from random import Random

MOD_MAX = int('9' * 6)
START_MAX = int('-' + '9' * 30)
END_MAX = int('9' * 30)


def gen_arithmetic(start, end, op, num):
    rand = Random()
    for _ in range(num):
        first = rand.randint(start, end)
        second = rand.randint(start, end)
        result = eval(f'{first}{op}{second}')
        if op == '/':
            if second == 0:
                while second != 0:
                    second = rand.randint(start, end)
                result = eval(f'{first}{op}{second}')
                result = int(result)
            else:
                result = int(result)
        print("{}{}{}={}".format(str(first), op, str(second), result))


def gen_mod_arithmetic(start, end, num):
    rand = Random()
    for _ in range(num):
        first = rand.randint(start, end)
        second = rand.randint(0, MOD_MAX)
        op = '%'
        print("{}{}{}={}".format(str(first), op, str(second), str(first % second)))


if __name__ == '__main__':
    for _ in range(10000):
        if Random().choice([0, 1, 2, 3, 4]) == 4:
            gen_mod_arithmetic(0, END_MAX, 1)
        else:
            gen_arithmetic(START_MAX, END_MAX, Random().choice(['*', '-', '+', '/']), 1)
