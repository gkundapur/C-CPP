#! /usr/bin/python

import time

def get_square(n):
    return n * n

memo = {}
def get_square_memo(n):
    if(n in memo): return memo[n]

    memo[n] = n*n
    return memo[n]

print("With get_square()\n-----------------")
start = time.time()
print(get_square(30000))
end = time.time()
total_1 = round((end - start)*1000, 5)
print("First Call: ", total_1, "s\n")

print("With get_square_memo()\n----------------------")
startA = time.time()
print(get_square_memo(30000))
endA = time.time()
total_2 = round((endA - startA)*1000, 5)
print("First Call: ", total_2, "ms")

startB = time.time()
print(get_square_memo(30000))
endB = time.time()
total_3 = round((endB - startB)*1000, 5)
print("Second Call: ", total_3, "ms")

