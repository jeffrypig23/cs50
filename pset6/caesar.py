from sys import argv
import string

# Check if there is a valid number of arguments (just the 1 after the name)
if (len(argv) != 2):
    print("Usage: ./caesar <positive number>")
    exit(1)
else:
    offset = int(argv[1])

    # Check offset
    while (offset > 26):
        offset = offset - 26

    enteredText = str(input("plaintext: "))

    cipheredText = ""
    offsetChar = 0

    # Offset the ciphered text by the applied offset
    for i in range(len(enteredText)):

        # Check if the entered character is alphabetical, if not, just add it
        if (enteredText[i].isalpha()):

            # Create the final offset value for the character
            offsetChar = ord(enteredText[i]) + offset

            # Check if that offset character is alpha, and apply it
            if ((chr(offsetChar)).isalpha()):
                cipheredText += chr(offsetChar)
            else:
                # Get how far over the overflow it is, and then apply that as the offset
                offsetChar = 97 + (offsetChar - 123)
                cipheredText += chr(offsetChar)

        else:
            cipheredText += enteredText[i]

    print("ciphertext: {}".format(cipheredText))