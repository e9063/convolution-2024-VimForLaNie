#
# 01204332 OPERATING SYSTEMS
# --------------------------
# 
# Assignment Set 2024/1, Task A
# Companion Program to Generate Test Cases
#
# Result correctness is guaranteed. However, program error checking is NOT guaranteed.
# Use at your own risk.
#


import numpy as np
import sys

if len(sys.argv) > 1:
    name = sys.argv[1]

if len(sys.argv) > 2:
    try:
        NA = int(sys.argv[2])
        if NA < 0:
            raise ValueError('arg 2 will be used as array size. Make it positive int.')
    except TypeError:
        raise TypeError('arg 2 will be used as array size. Make it positive int.')
else:
    NA = 1000000
    NF = 10000

if len(sys.argv) > 3:
    try:
        NF = int(sys.argv[3])
        if NF < 0:
            raise ValueError('arg 3 will be used as filter size. Make it positive int.')
        elif NF > NA:
            raise ValueError('arg 2 is array, arg 3 is filter. Must make filter shorter than array!')
    except TypeError:
        raise TypeError('arg 3 will be used as filter size. Make it positive int.')

A = np.random.randint(0, 255, NA).astype('i8')
F = np.random.randint(0, 255, NF).astype('i8')
B = np.convolve(A, F, mode='valid')

if len(sys.argv) > 1:
    print("writing input . . .")
    with open(f'input_{name}.txt', 'w') as input_file:
        print(f'{NA} {NF}', file = input_file)
        print(*A, sep='\n', file = input_file)
        print(*F, sep='\n', file = input_file)
    print("writing output . . .")
    with open(f'output_{name}.txt', 'w') as output_file:
        print(*B, sep='\n', file = output_file)

