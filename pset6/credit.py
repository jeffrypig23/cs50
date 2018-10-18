# git smort boiiiii
import math


def main():
    # Get the users credit card number
    ccn = -1
    while (ccn < 0):
        try:
            ccn = int(input("Gimmie ur credit card #: "))
        except:
            ccn = -1.0

    # Check if the number is invalid off the bat
    if (math.floor(math.log10(abs(ccn))) + 1 < 13):
        print("INVALID")
    else:
        # Check if te number matches the algorithm
        if (checkLuhn(ccn) == 0):
            first = int(str(ccn)[0])
            second = int(str(ccn)[1])
            if (first is 4):
                # If its 4, its visa
                print("VISA")
            elif (first is 3 and (second is 4 or second is 7)):
                # If it starts with 3 and then either 4 or 7, its american express
                print("AMEX")
            elif (first is 5 and (second is 1 or second is 2 or second is 3 or second is 4 or second is 5)):
                # If it starts with 5 and then either 1 - 5, its mastercard
                print("MASTERCARD")
            else:
                print("INVALID")
        else:
            print("INVALID")


def checkLuhn(creditcardnumber):
    def digits_of(n):
        return [int(d) for d in str(n)]
    digits = digits_of(creditcardnumber)
    odd_digits = digits[-1::-2]
    even_digits = digits[-2::-2]
    checksum = 0
    checksum += sum(odd_digits)
    for d in even_digits:
        checksum += sum(digits_of(d * 2))
    return checksum % 10


if __name__ == "__main__":
    main()