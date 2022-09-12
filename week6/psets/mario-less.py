while True:
    try:
        height = int(input("Height: "))
    except:
        continue
    if (height > 0 and height < 9):
        break
counter = 1
while counter != height+1:
    print(" " * (height - counter), end="")
    print("#"*counter, end="")
    print("")
    counter += 1
