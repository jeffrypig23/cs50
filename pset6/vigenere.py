import sys
import string

if (len(sys.argv) is not 2):
    # If invalid arguments are provided (too many), quit due to error
    print("Usage: ./vigenere <string>")
    exit(1)
else:

    # Create a variable for the offsets
    offsets = []
    for offsetparser in range(len(sys.argv[1])):

        # Check if the character entered is alpha
        if ((sys.argv[1][offsetparser]).isalpha()):
            # Set it to uppercase, and then store the offset value, from 0 - 26 ('A' - 'Z')
            offsets.append(ord(sys.argv[1][offsetparser].upper()) - ord('A'))
        else:
            # If invalid arguments are provided, quit due to error
            print("Usage: ./vigenere <string>")
            exit(1)

    enteredText = str(input("plaintext: "))
    o = 0
    cipheredText = ""

    # Offset the ciphered text by the applied offset
    for i in range(len(enteredText)):

        # Check if the entered character is alphabetical, if not, just add it
        if (enteredText[i].isalpha()):

            # Create the final offset value for the character
            offsetChar = ord(enteredText[i]) + offsets[o]

            # Do seperate things for upper and lowercase letters
            if (enteredText[i].isupper()):

                # Check of the offset character is within the uppercase bounds
                if (offsetChar >= ord("A") and offsetChar <= ord("Z")):
                    # Apply the offset
                    cipheredText += chr(offsetChar)
                else:
                    # Get how large the overflow is, and then apply that as the offset
                    offsetChar = offsetChar - 26
                    cipheredText += chr(offsetChar)

            else:
                # Check of the offset character is within the uppercase bounds
                if (offsetChar >= ord("a") and offsetChar <= ord("z")):
                    # Apply the offset
                    cipheredText += chr(offsetChar)
                else:
                    # Get how large the overflow is, and then apply that as the offset
                    offsetChar = offsetChar - 26
                    cipheredText += chr(offsetChar)

            print("Offset char: {0}({1})".format(offsetChar, chr(offsetChar)))

            # Reset the offset
            o += 1
            if (o > len(offsets) - 1):
                o = 0

        else:
            cipheredText += enteredText[i]

    print("ciphertext: {}".format(cipheredText))