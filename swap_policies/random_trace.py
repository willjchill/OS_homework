import random

f = open("random_trace.txt", "w")
for i in range(20):
    f.write(f"{random.randint(0, 9)} \n")
f.close()
