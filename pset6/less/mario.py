# Get the height from the user
height = -1
while ((height < 1 or height > 23) and height != 0):
    try:
        height = int(input("Height: "))
    except:
        height = -1

# Set aside a value for the number of spaces and hashes
spaceValue = height - 1
hashValue = 2

for i in range(height):
    # Print a space for the total amount of the space value
    print(" " * spaceValue, end='')

    # Print a hash for the total hash value
    print("#" * hashValue, end='')

    # Change the values
    spaceValue -= 1
    hashValue += 1

    # Print a new line
    print("")