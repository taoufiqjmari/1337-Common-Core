import random

args_num = int(input())
args = []
args = random.sample(range(args_num), args_num)
print(' '.join([str(i) for i in args]))