from cs50 import get_float
pennies = 0.01
nickels = 0.05
dimes = 0.1
quarters = 0.25

counter = 0
while True:
    change = get_float("C: ")
    if change > 0:
        break
while change >= quarters:
    counter += 1
    change -= quarters

while change >= dimes:
    counter += 1
    change -= dimes

while change >= nickels:
    counter += 1
    change -= nickels

while change >= pennies:
    counter += 1
    change -= dimes

print(counter)
