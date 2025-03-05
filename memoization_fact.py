#! /usr/bin/python
import time

memory = {}

def facto(num):
	if num < 2:
		return 1
	return num * facto(num - 1)

def facto_memo(num):
	if num < 2:
		return 1

	if num not in memory:
		memory[num] = num * facto_memo(num - 1)
	return memory[num]

print("With facto()\n------------------------")
start = time.time()
print(facto(5))
end = time.time()
total_1 = round((end - start) * 1000, 5)
print("First call: ", total_1, "ms\n")

print("With facto_memo()\n---------------------")
startA = time.time()
print(facto_memo(5))
endA = time.time()
total_2 = round((endA - startA) * 1000, 5)
print("First call: ", total_2, "ms\n")

startB = time.time()
print(facto_memo(5))
endB = time.time()
total_3 = round((endB - startB) * 1000, 5)
print("Second call: ", total_3, "ms\n")

print("With facto()\n------------------------")
start = time.time()
print(facto(6))
end = time.time()
total_1 = round((end - start) * 1000, 5)

print("First call: ", total_1, "ms\n")
startC = time.time()
print(facto_memo(6))
endC = time.time()
total_3 = round((endC - startC) * 1000, 5)
print("Second call: ", total_3, "ms\n")
