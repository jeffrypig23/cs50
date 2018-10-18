# Get input for the user
valueOwed = -1.0
while (valueOwed < 0.0):
    try:
        valueOwed = float(input("How much do I owe joo? "))
    except:
        valueOwed = -1.0

# Set aside value for the amount to be returned
amount = 0

roundValue = round(valueOwed * 100)

# Calculate quarters due
while(roundValue - 25 >= 0):
    amount += 1
    roundValue = roundValue - 25

# Calculate dimes due
while(roundValue - 10 >= 0):
    amount += 1
    roundValue = roundValue - 10

# Calculate nickels due
while(roundValue - 5 >= 0):
    amount += 1
    roundValue = roundValue - 5

# Calculate paper weights due
while(roundValue - 1 >= 0):
    amount += 1
    roundValue = roundValue - 1

print(amount)