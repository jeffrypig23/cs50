import crypt
import sys


def main():
    if (len(sys.argv) is not 2):
        print("Usage: ./crack <hash>")
        exit(1)
    else:
        salt = sys.argv[1][:-2]
        #print("Salt: {}".format(salt))
        crack(password_hash=sys.argv[1], salt=salt)


def crack(password_hash, salt):
    # Initalize the guess string to blanks
    guessString = ['', '', '', '', '']
    validated = False

    # Itterate through each character and add onto it and then check it
    # Brute force ftw
    for a in range(ord("A"), ord("z")):
        if (a == 91):
            a = 97
        for b in range(ord("A"), ord("z")):
            if (b == 91):
                b = 97
            for c in range(ord("A"), ord("z")):
                if (c == 91):
                    c = 97
                for d in range(ord("A"), ord("z")):
                    if (d == 91):
                        d = 97
                    for e in range(ord("A"), ord("z")):
                        if (e == 91):
                            e = 97
                        guessString[0] = chr(e)
                        # Just for testing purposes, lets see what happens when I set the string to ROFL
                        strHash = crypt.crypt("".join(guessString), salt)
                        #strHash = crypt.crypt("rofl", salt)
                        if (strHash == password_hash):
                            validated = True
                        # Fun debugging log :D
                        # print("Trying combo: {0}\nGiven hash: {1}\nHash: {2}\nValid?: {3}\n".format(guessString, password_hash, strHash, validated));
                        if (validated):
                            # If Validated, then set the password, print it, and then exit
                            password = "".join(guessString)
                            print(password)
                            exit(0)
                    guessString[1] = chr(d)
                guessString[2] = chr(c)
            guessString[3] = chr(b)
        guessString[4] = chr(a)


if __name__ == "__main__":
    main()